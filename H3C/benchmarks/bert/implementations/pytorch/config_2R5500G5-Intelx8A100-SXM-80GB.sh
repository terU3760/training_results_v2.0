## DL params
export BATCHSIZE=28
export GRADIENT_STEPS=1
export LR=4e-4
export MAX_SAMPLES_TERMINATION=4500000
export MAX_STEPS=7100
export OPT_LAMB_BETA_1=0.9
export OPT_LAMB_BETA_2=0.999
export START_WARMUP_STEP=0
#export WARMUP_STEPS=

export SBATCH_NETWORK=sharp
export EXTRA_PARAMS="--dense_seq_output --unpad --unpad_fmha --exchange_padding --fused_bias_fc --fused_bias_mha --fused_dropout_add  --fused_gemm_gelu "
export PHASE=2
export EVAL_ITER_START_SAMPLES=150000
export EVAL_ITER_SAMPLES=150000

## System run parms
export DGXNNODES=2
export DGXSYSTEM=$(basename $(readlink -f ${BASH_SOURCE[0]}) | sed 's/^config_//' | sed 's/\.sh$//' )
export WALLTIME_MINUTES=15
export WALLTIME=$(( ${NEXP:-1} * ${WALLTIME_MINUTES} + 5 ))

## System config params
source $(dirname ${BASH_SOURCE[0]})/config_2R5500G5-Intelx8A100-SXM-80GB_common.sh
