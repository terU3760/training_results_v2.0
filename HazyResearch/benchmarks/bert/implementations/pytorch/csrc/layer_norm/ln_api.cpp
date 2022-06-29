#include <torch/extension.h>
#include "ATen/cuda/CUDAContext.h"

#include "ln.h"

/*

Supported Type combinations:

input    compute   weights   output    
=======================================
fp32     fp32      fp32      fp32      
fp16     fp32      fp16      fp16      
bf16     fp32      bf16      bf16      
fp32     fp32      fp16      fp16      
fp32     fp32      bf16      bf16      

Remarks:
Output type = Weight type
Compute always in FP32

*/

namespace layer_norm {

// Create registries and provide runtime versions of config hash functions.

FwdRegistry FWD_FUNCS;
BwdRegistry BWD_FUNCS;

////////////////////////////////////////////////////////////////////////////////////////////////////

uint32_t get_type_id(torch::Dtype dtype){
    if( dtype == torch::kFloat16 ) {
        return TypeId<fp16>::Value;
    } else if( dtype == torch::kBFloat16 ) {
        return TypeId<bf16>::Value;
    } else if( dtype == torch::kFloat32 ) {
        return TypeId<fp32>::Value;
    } else {
        TORCH_CHECK(false, "Type not supported: ", dtype);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t get_key(torch::Dtype wtype, torch::Dtype itype, torch::Dtype otype, torch::Dtype ctype, uint64_t hidden_size) {
    using namespace layer_norm;
    uint64_t type_key = get_type_id(wtype) | (get_type_id(itype) << 2) | (get_type_id(otype) << 4) | (get_type_id(ctype) << 6);
    uint64_t launcher_key = (type_key << 32) | hidden_size;
    return launcher_key;
}

}  // namespace layer_norm

////////////////////////////////////////////////////////////////////////////////////////////////////

layer_norm::FwdFunction & get_fwd_launcher(torch::Dtype wtype, torch::Dtype itype, torch::Dtype otype, torch::Dtype ctype, uint32_t hidden_size) {
    auto iter = layer_norm::FWD_FUNCS.find(layer_norm::get_key(wtype, itype, otype, ctype, hidden_size));
    if( iter != layer_norm::FWD_FUNCS.end() ) {
        return iter->second;
    } else {
        TORCH_CHECK(false, "FWD: Unsupported hidden_size or types: ", hidden_size, wtype, itype, otype, ctype);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

layer_norm::BwdFunction & get_bwd_launcher(torch::Dtype wtype, torch::Dtype itype, torch::Dtype otype, torch::Dtype ctype, uint32_t hidden_size) {
    auto iter = layer_norm::BWD_FUNCS.find(layer_norm::get_key(wtype, itype, otype, ctype, hidden_size));
    if( iter != layer_norm::BWD_FUNCS.end() ) {
        return iter->second;
    } else {
        TORCH_CHECK(false, "BWD: Unsupported hidden_size or types: ", hidden_size, wtype, itype, otype, ctype);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<at::Tensor> dropout_add_ln_fwd(const at::Tensor &x0,      // BxSxhidden_size
                                           const at::Tensor &x1,      // BxSxhidden_size
                                           const at::Tensor &gamma,   // hidden_size
                                           const at::Tensor &beta,   // hidden_size
                                           const float dropout_p,
                                           const float epsilon,
                                           c10::optional<at::Generator> gen_
) {
    auto itype = x0.scalar_type();
    auto wtype = gamma.scalar_type();
    auto otype = wtype;
    auto ctype = torch::kFloat32;
    auto mtype = torch::kUInt8;

    TORCH_CHECK(x1.scalar_type() == itype);
    TORCH_CHECK(beta.scalar_type() == wtype);

    TORCH_CHECK(x0.is_cuda())
    TORCH_CHECK(x1.is_cuda())
    TORCH_CHECK(gamma.is_cuda())
    TORCH_CHECK(beta.is_cuda())

    TORCH_CHECK(x0.is_contiguous());
    TORCH_CHECK(x1.is_contiguous());
    auto sizes = x0.sizes();
    TORCH_CHECK(sizes.size() == 2);
    TORCH_CHECK(x1.sizes() == sizes);

    const int rows = sizes[0];
    const int cols = sizes[1];
    auto hidden_size = gamma.numel();

    TORCH_CHECK(gamma.sizes() == beta.sizes());
    TORCH_CHECK(hidden_size == cols);

    TORCH_CHECK(epsilon >= 0.f);

    auto opts = x0.options();

    auto x = torch::empty(sizes, opts.dtype(otype));
    auto dmask = torch::empty(sizes, opts.dtype(mtype));
    auto z = torch::empty(sizes, opts.dtype(otype));

    auto mu = torch::empty({ rows }, opts.dtype(ctype));
    auto rsigma = torch::empty({ rows }, opts.dtype(ctype));

    layer_norm::LaunchParams<layer_norm::FwdParams> launch_params;

    launch_params.props = at::cuda::getCurrentDeviceProperties();
    launch_params.stream = at::cuda::getCurrentCUDAStream().stream();

    auto gen = at::get_generator_or_default<at::CUDAGeneratorImpl>(
        gen_, at::cuda::detail::getDefaultCUDAGenerator());

    // Request the kernel launcher.
    auto launcher = get_fwd_launcher(wtype, itype, otype, ctype, hidden_size);

    // Query the kernel-specific launch parameters.
    launcher(launch_params, true);

    at::Tensor workspace, barrier;

    // Set the kernel runtime parameters.
    layer_norm::FwdParams &params = launch_params.params;
    params.rows = rows;
    params.cols = cols;
    params.x0 = x0.data_ptr();
    params.x1 = x1.data_ptr();
    params.x = x.data_ptr();
    params.dmask = dmask.data_ptr();
    params.mu = mu.data_ptr();
    params.rs = rsigma.data_ptr();
    params.gamma = gamma.data_ptr();
    params.beta = beta.data_ptr();
    params.z = z.data_ptr();
    params.epsilon = epsilon;
    TORCH_CHECK(dropout_p < 1.f);
    params.dropout_keep_p = 1.f - dropout_p;
    params.dropout_scale = 1.f / (1.f - dropout_p);

    // number of times random will be generated per thread, to offset philox counter in thc random
    // state
    int64_t counter_offset = launch_params.elts_per_thread;

    // See Note [Acquire lock when using random generators]
    {
        std::lock_guard<std::mutex> lock(gen->mutex_);
        params.philox_args = gen->philox_cuda_state(counter_offset);
    }

    if( launch_params.barrier_size > 0 ) {
        auto options = x0.options();
        barrier = torch::zeros(launch_params.barrier_size, options.dtype(torch::kInt32));
        workspace = torch::empty(launch_params.workspace_bytes, options.dtype(torch::kChar));
        params.workspace = workspace.data_ptr();
        params.barrier = barrier.data_ptr<int>();
    }

    // Launch the kernel.
    launcher(launch_params, false);

    return { z, x, dmask, mu, rsigma };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<at::Tensor> dropout_add_ln_bwd(const at::Tensor &dz,     // BxSxhidden_size
                                           const at::Tensor &x,      // BxSxhidden_size
                                           const at::Tensor &dmask,  // BxSxhidden_size
                                           const at::Tensor &mu,     // BxS, FP32!
                                           const at::Tensor &rsigma, // BxS, FP32!
                                           const at::Tensor &gamma,   // hidden_size
                                           const float dropout_p
) {

    auto itype = x.scalar_type();
    auto wtype = gamma.scalar_type();
    auto otype = wtype;
    auto ctype = torch::kFloat32;
    auto mtype = torch::kUInt8;

    TORCH_CHECK(dmask.dtype() == mtype);
    TORCH_CHECK(dz.dtype() == otype);
    TORCH_CHECK(mu.dtype() == ctype);
    TORCH_CHECK(rsigma.dtype() == ctype);

    TORCH_CHECK(x.is_cuda());
    TORCH_CHECK(dmask.is_cuda());
    TORCH_CHECK(dz.is_cuda());
    TORCH_CHECK(mu.is_cuda());
    TORCH_CHECK(rsigma.is_cuda());
    TORCH_CHECK(gamma.is_cuda());

    TORCH_CHECK(x.is_contiguous());
    TORCH_CHECK(dmask.is_contiguous());
    TORCH_CHECK(dz.is_contiguous());

    auto sizes = x.sizes();
    TORCH_CHECK(sizes.size() == 2);
    TORCH_CHECK(dmask.sizes() == sizes);
    TORCH_CHECK(dz.sizes() == sizes);
    auto rows = sizes[0];
    auto cols = sizes[1];

    auto hidden_size = gamma.numel();

    TORCH_CHECK(mu.numel() == rows);
    TORCH_CHECK(mu.sizes() == rsigma.sizes());

    TORCH_CHECK(gamma.numel() == cols);

    auto options = x.options();

    auto dx0 = torch::empty_like(x);
    auto dx1 = torch::empty_like(x);
    auto dgamma = torch::empty_like(gamma);
    auto dbeta = torch::empty_like(gamma);

    layer_norm::LaunchParams<layer_norm::BwdParams> launch_params;
    launch_params.stream = at::cuda::getCurrentCUDAStream().stream();
    launch_params.props = at::cuda::getCurrentDeviceProperties();

    auto launcher = get_bwd_launcher(wtype, itype, otype, ctype, hidden_size);

    launcher(launch_params, true);

    auto dgamma_part = torch::empty({ launch_params.params.ctas_per_col, hidden_size }, options.dtype(ctype));
    auto dbeta_part = torch::empty({ launch_params.params.ctas_per_col, hidden_size }, options.dtype(ctype));
    at::Tensor workspace, barrier;

    layer_norm::BwdParams &params = launch_params.params;
    params.rows = rows;
    params.cols = cols;
    params.x = x.data_ptr();
    params.dmask = dmask.data_ptr();
    params.mu = mu.data_ptr();
    params.rs = rsigma.data_ptr();
    params.gamma = gamma.data_ptr();
    params.dz = dz.data_ptr();
    params.dx0 = dx0.data_ptr();
    params.dx1 = dx1.data_ptr();
    params.dbeta = dbeta.data_ptr();
    params.dgamma = dgamma.data_ptr();
    params.dbeta_part = dbeta_part.data_ptr();
    params.dgamma_part = dgamma_part.data_ptr();
    TORCH_CHECK(dropout_p < 1.f);
    params.dropout_scale = 1.f / (1.f - dropout_p);

    if( launch_params.barrier_size > 0 ) {
        // TODO Any way to avoid this?
        barrier = torch::zeros(launch_params.barrier_size, options.dtype(torch::kInt32));
        workspace = torch::empty(launch_params.workspace_bytes, options.dtype(torch::kChar));
        params.workspace = workspace.data_ptr();
        params.barrier = barrier.data_ptr<int>();
    }

    launcher(launch_params, false);

    return { dx0, dx1, dgamma, dbeta, dgamma_part, dbeta_part };
}

////////////////////////////////////////////////////////////////////////////////////////////////////

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.doc() = "CUDA DropoutAddLayerNorm";
  m.def("dropout_add_ln_fwd", &dropout_add_ln_fwd, "Run LayerNorm forward kernel");
  m.def("dropout_add_ln_bwd", &dropout_add_ln_bwd, "Run LayerNorm backward kernel");
}