//////////////////////////////////////////////////////////////////////
// This file was automatically generated by PyCLIF.
// Version 0.3
//////////////////////////////////////////////////////////////////////
// source: /tmp/clif/examples/postprocess/python/postprocess.clif

#include <Python.h>

namespace postprocess_python_postprocess_clifwrap {

bool Ready();
PyObject* Init();

}  // namespace postprocess_python_postprocess_clifwrap

PyMODINIT_FUNC PyInit_postprocess(void) {
  if (!postprocess_python_postprocess_clifwrap::Ready()) return nullptr;
  return postprocess_python_postprocess_clifwrap::Init();
}
