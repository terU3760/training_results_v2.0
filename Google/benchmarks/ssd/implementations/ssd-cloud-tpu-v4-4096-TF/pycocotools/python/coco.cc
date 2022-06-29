//////////////////////////////////////////////////////////////////////
// This file was automatically generated by PyCLIF.
// Version 0.3
//////////////////////////////////////////////////////////////////////
// source: /tmp/clif/examples/pycocotools/python/coco.clif

#include <Python.h>
#include "absl/memory/memory.h"
#include "absl/types/optional.h"
#include "/usr/local/lib/python3.7/dist-packages/clif/python/types.h"
#include "coco_clif.h"
#include "clif/python/stltypes.h"
#include "clif/python/slots.h"

namespace pycocotools_python_coco_clifwrap {

using namespace clif;

static const char* ThisModuleName = "pycocotools.python.coco";

#define _0 py::postconv::PASS
#define _1 UnicodeFromBytes
#define _2 UnicodeFromBytes

namespace pyCOCO {

struct wrapper {
  PyObject_HEAD
  ::clif::Instance<::pycocotools::COCO> cpp;
  PyObject* instance_dict = nullptr;
  PyObject* weakrefs = nullptr;
};

static ::pycocotools::COCO* ThisPtr(PyObject*);

// __init__(annotation_file:str, use_mask:bool)
static PyObject* wrapCOCO_as___init__(PyObject* self, PyObject* args, PyObject* kw) {
  PyObject* a[2];
  const char* names[] = {
      "annotation_file",
      "use_mask",
      nullptr
  };
  if (!PyArg_ParseTupleAndKeywords(args, kw, "OO:__init__", const_cast<char**>(names), &a[0], &a[1])) return nullptr;
  ::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>> arg1;
  if (!Clif_PyObjAs(a[0], &arg1)) return ArgError("__init__", names[0], "::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>>", a[0]);
  bool arg2;
  if (!Clif_PyObjAs(a[1], &arg2)) return ArgError("__init__", names[1], "bool", a[1]);
  // Call actual C++ method.
  Py_INCREF(args);
  Py_XINCREF(kw);
  PyThreadState* _save;
  Py_UNBLOCK_THREADS
  PyObject* err_type = nullptr;
  std::string err_msg{"C++ exception"};
  try {
    reinterpret_cast<wrapper*>(self)->cpp = ::clif::MakeShared<::pycocotools::COCO>(std::move(arg1), std::move(arg2));
  } catch(const std::exception& e) {
    err_type = PyExc_RuntimeError;
    err_msg += std::string(": ") + e.what();
  } catch (...) {
    err_type = PyExc_RuntimeError;
  }
  Py_BLOCK_THREADS
  Py_DECREF(args);
  Py_XDECREF(kw);
  if (err_type) {
    PyErr_SetString(err_type, err_msg.c_str());
    return nullptr;
  }
  Py_RETURN_NONE;
}

// LoadRes(py_object:object) -> COCO
static PyObject* wrapLoadRes(PyObject* self, PyObject* args, PyObject* kw) {
  PyObject* a[1];
  const char* names[] = {
      "py_object",
      nullptr
  };
  if (!PyArg_ParseTupleAndKeywords(args, kw, "O:LoadRes", const_cast<char**>(names), &a[0])) return nullptr;
  ::_object * arg1;
  if (!Clif_PyObjAs(a[0], &arg1)) return ArgError("LoadRes", names[0], "::_object *", a[0]);
  // Call actual C++ method.
  ::pycocotools::COCO* c = ThisPtr(self);
  if (!c) return nullptr;
  ::pycocotools::COCO ret0;
  PyObject* err_type = nullptr;
  std::string err_msg{"C++ exception"};
  try {
    ret0 = c->LoadRes(arg1);
  } catch(const std::exception& e) {
    err_type = PyExc_RuntimeError;
    err_msg += std::string(": ") + e.what();
  } catch (...) {
    err_type = PyExc_RuntimeError;
  }
  if (err_type) {
    PyErr_SetString(err_type, err_msg.c_str());
    return nullptr;
  }
  return Clif_PyObjFrom(std::move(ret0), {});
}

// LoadResMask(py_object:object, py_mask_object:object) -> COCO
static PyObject* wrapLoadResMask(PyObject* self, PyObject* args, PyObject* kw) {
  PyObject* a[2];
  const char* names[] = {
      "py_object",
      "py_mask_object",
      nullptr
  };
  if (!PyArg_ParseTupleAndKeywords(args, kw, "OO:LoadResMask", const_cast<char**>(names), &a[0], &a[1])) return nullptr;
  ::_object * arg1;
  if (!Clif_PyObjAs(a[0], &arg1)) return ArgError("LoadResMask", names[0], "::_object *", a[0]);
  ::_object * arg2;
  if (!Clif_PyObjAs(a[1], &arg2)) return ArgError("LoadResMask", names[1], "::_object *", a[1]);
  // Call actual C++ method.
  ::pycocotools::COCO* c = ThisPtr(self);
  if (!c) return nullptr;
  ::pycocotools::COCO ret0;
  PyObject* err_type = nullptr;
  std::string err_msg{"C++ exception"};
  try {
    ret0 = c->LoadResMask(arg1, arg2);
  } catch(const std::exception& e) {
    err_type = PyExc_RuntimeError;
    err_msg += std::string(": ") + e.what();
  } catch (...) {
    err_type = PyExc_RuntimeError;
  }
  if (err_type) {
    PyErr_SetString(err_type, err_msg.c_str());
    return nullptr;
  }
  return Clif_PyObjFrom(std::move(ret0), {});
}

static PyMethodDef MethodsStaticAlloc[] = {
  {"__init__", (PyCFunction)wrapCOCO_as___init__, METH_VARARGS | METH_KEYWORDS, "__init__(annotation_file:str, use_mask:bool)\n  Calls C++ function\n  void ::pycocotools::COCO::COCO(::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>>, bool)"},
  {"LoadRes", (PyCFunction)wrapLoadRes, METH_VARARGS | METH_KEYWORDS, "LoadRes(py_object:object) -> COCO\n  Calls C++ function\n  ::pycocotools::COCO ::pycocotools::COCO::LoadRes(::_object *)"},
  {"LoadResMask", (PyCFunction)wrapLoadResMask, METH_VARARGS | METH_KEYWORDS, "LoadResMask(py_object:object, py_mask_object:object) -> COCO\n  Calls C++ function\n  ::pycocotools::COCO ::pycocotools::COCO::LoadResMask(::_object *, ::_object *)"},
  {"__reduce_ex__", (PyCFunction)::clif::ReduceExImpl, METH_VARARGS | METH_KEYWORDS, "Helper for pickle."},
  {}
};

// COCO __init__
static int _ctor(PyObject* self, PyObject* args, PyObject* kw);

// COCO __new__
static PyObject* _new(PyTypeObject* type, Py_ssize_t nitems);

// COCO __del__
static void _dtor(PyObject* self) {
  if (reinterpret_cast<wrapper*>(self)->weakrefs) {
    PyObject_ClearWeakRefs(self);
  }
  Py_BEGIN_ALLOW_THREADS
  reinterpret_cast<wrapper*>(self)->cpp.Destruct();
  Py_END_ALLOW_THREADS
  Py_TYPE(self)->tp_free(self);
}

static void _del(void* self) {
  delete reinterpret_cast<wrapper*>(self);
}

PyTypeObject* wrapper_Type = nullptr;

static PyTypeObject* _build_heap_type() {
  PyHeapTypeObject *heap_type =
      (PyHeapTypeObject *) PyType_Type.tp_alloc(&PyType_Type, 0);
  if (!heap_type)
    return nullptr;
  heap_type->ht_qualname = (PyObject *) PyUnicode_FromString(
      "COCO");
  Py_INCREF(heap_type->ht_qualname);
  heap_type->ht_name = heap_type->ht_qualname;
  PyTypeObject *ty = &heap_type->ht_type;
  ty->tp_as_number = &heap_type->as_number;
  ty->tp_as_sequence = &heap_type->as_sequence;
  ty->tp_as_mapping = &heap_type->as_mapping;
#if PY_VERSION_HEX >= 0x03050000
  ty->tp_as_async = &heap_type->as_async;
#endif
  ty->tp_name = "pycocotools.python.coco.COCO";
  ty->tp_basicsize = sizeof(wrapper);
  ty->tp_dealloc = _dtor;
  ty->tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE;
  ty->tp_doc = "CLIF wrapper for ::pycocotools::COCO";
  ty->tp_methods = MethodsStaticAlloc;
  ty->tp_init = _ctor;
  ty->tp_alloc = _new;
  ty->tp_new = PyType_GenericNew;
  ty->tp_free = _del;
  ty->tp_weaklistoffset = offsetof(wrapper, weakrefs);
  return ty;
}

static int _ctor(PyObject* self, PyObject* args, PyObject* kw) {
  PyObject* init = wrapCOCO_as___init__(self, args, kw);
  Py_XDECREF(init);
  return init? 0: -1;
}

static PyObject* _new(PyTypeObject* type, Py_ssize_t nitems) {
  DCHECK(nitems == 0);
  wrapper* wobj = new wrapper;
  PyObject* self = reinterpret_cast<PyObject*>(wobj);
  return PyObject_Init(self, wrapper_Type);
}

static ::pycocotools::COCO* ThisPtr(PyObject* py) {
  if (Py_TYPE(py) == wrapper_Type) {
    return ::clif::python::Get(reinterpret_cast<wrapper*>(py)->cpp);
  }
  PyObject* base = PyObject_CallMethod(py, "as_pycocotools_COCO", nullptr);
  if (base == nullptr) {
    PyErr_Clear();
  } else {
    if (PyCapsule_CheckExact(base)) {
      void* p = PyCapsule_GetPointer(base, "::pycocotools::COCO");
      if (!PyErr_Occurred()) {
        ::pycocotools::COCO* c = static_cast<::pycocotools::COCO*>(p);
        Py_DECREF(base);
        return c;
      }
    }
    Py_DECREF(base);
  }
  if (PyObject_IsInstance(py, reinterpret_cast<PyObject*>(wrapper_Type))) {
    if (!base) {
      return ::clif::python::Get(reinterpret_cast<wrapper*>(py)->cpp);
    }
    PyErr_Format(PyExc_ValueError, "can't convert %s %s to ::pycocotools::COCO*", ClassName(py), ClassType(py));
  } else {
    PyErr_Format(PyExc_TypeError, "expecting %s instance, got %s %s", wrapper_Type->tp_name, ClassName(py), ClassType(py));
  }
  return nullptr;
}

}  // namespace pyCOCO

namespace pyCOCOeval {

struct wrapper {
  PyObject_HEAD
  ::clif::Instance<::pycocotools::COCOeval> cpp;
  PyObject* instance_dict = nullptr;
  PyObject* weakrefs = nullptr;
};

static ::pycocotools::COCOeval* ThisPtr(PyObject*);

// __init__(coco_gt:COCO, coco_dt:COCO, iou_type:str)
static PyObject* wrapCOCOeval_as___init__(PyObject* self, PyObject* args, PyObject* kw) {
  PyObject* a[3];
  const char* names[] = {
      "coco_gt",
      "coco_dt",
      "iou_type",
      nullptr
  };
  if (!PyArg_ParseTupleAndKeywords(args, kw, "OOO:__init__", const_cast<char**>(names), &a[0], &a[1], &a[2])) return nullptr;
  ::pycocotools::COCO* arg1;
  if (!Clif_PyObjAs(a[0], &arg1)) return ArgError("__init__", names[0], "::pycocotools::COCO", a[0]);
  if (arg1 == nullptr) {
    return ArgError("__init__", names[0], "::pycocotools::COCO", a[0]);
  }
  ::pycocotools::COCO* arg2;
  if (!Clif_PyObjAs(a[1], &arg2)) return ArgError("__init__", names[1], "::pycocotools::COCO", a[1]);
  if (arg2 == nullptr) {
    return ArgError("__init__", names[1], "::pycocotools::COCO", a[1]);
  }
  ::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>> arg3;
  if (!Clif_PyObjAs(a[2], &arg3)) return ArgError("__init__", names[2], "::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>>", a[2]);
  // Call actual C++ method.
  Py_INCREF(args);
  Py_XINCREF(kw);
  PyThreadState* _save;
  Py_UNBLOCK_THREADS
  PyObject* err_type = nullptr;
  std::string err_msg{"C++ exception"};
  try {
    reinterpret_cast<wrapper*>(self)->cpp = ::clif::MakeShared<::pycocotools::COCOeval>(*arg1, *arg2, std::move(arg3));
  } catch(const std::exception& e) {
    err_type = PyExc_RuntimeError;
    err_msg += std::string(": ") + e.what();
  } catch (...) {
    err_type = PyExc_RuntimeError;
  }
  Py_BLOCK_THREADS
  Py_DECREF(args);
  Py_XDECREF(kw);
  if (err_type) {
    PyErr_SetString(err_type, err_msg.c_str());
    return nullptr;
  }
  Py_RETURN_NONE;
}

// Evaluate()
static PyObject* wrapEvaluate(PyObject* self) {
  // Call actual C++ method.
  ::pycocotools::COCOeval* c = ThisPtr(self);
  if (!c) return nullptr;
  PyThreadState* _save;
  Py_UNBLOCK_THREADS
  PyObject* err_type = nullptr;
  std::string err_msg{"C++ exception"};
  try {
    c->Evaluate();
  } catch(const std::exception& e) {
    err_type = PyExc_RuntimeError;
    err_msg += std::string(": ") + e.what();
  } catch (...) {
    err_type = PyExc_RuntimeError;
  }
  Py_BLOCK_THREADS
  if (err_type) {
    PyErr_SetString(err_type, err_msg.c_str());
    return nullptr;
  }
  Py_RETURN_NONE;
}

// Accumulate()
static PyObject* wrapAccumulate(PyObject* self) {
  // Call actual C++ method.
  ::pycocotools::COCOeval* c = ThisPtr(self);
  if (!c) return nullptr;
  PyThreadState* _save;
  Py_UNBLOCK_THREADS
  PyObject* err_type = nullptr;
  std::string err_msg{"C++ exception"};
  try {
    c->Accumulate();
  } catch(const std::exception& e) {
    err_type = PyExc_RuntimeError;
    err_msg += std::string(": ") + e.what();
  } catch (...) {
    err_type = PyExc_RuntimeError;
  }
  Py_BLOCK_THREADS
  if (err_type) {
    PyErr_SetString(err_type, err_msg.c_str());
    return nullptr;
  }
  Py_RETURN_NONE;
}

// Summarize()
static PyObject* wrapSummarize(PyObject* self) {
  // Call actual C++ method.
  ::pycocotools::COCOeval* c = ThisPtr(self);
  if (!c) return nullptr;
  PyThreadState* _save;
  Py_UNBLOCK_THREADS
  PyObject* err_type = nullptr;
  std::string err_msg{"C++ exception"};
  try {
    c->Summarize();
  } catch(const std::exception& e) {
    err_type = PyExc_RuntimeError;
    err_msg += std::string(": ") + e.what();
  } catch (...) {
    err_type = PyExc_RuntimeError;
  }
  Py_BLOCK_THREADS
  if (err_type) {
    PyErr_SetString(err_type, err_msg.c_str());
    return nullptr;
  }
  Py_RETURN_NONE;
}

// GetStats() -> list<float>
static PyObject* wrapGetStats(PyObject* self) {
  // Call actual C++ method.
  ::pycocotools::COCOeval* c = ThisPtr(self);
  if (!c) return nullptr;
  PyThreadState* _save;
  Py_UNBLOCK_THREADS
  ::std::vector<float> ret0;
  PyObject* err_type = nullptr;
  std::string err_msg{"C++ exception"};
  try {
    ret0 = c->GetStats();
  } catch(const std::exception& e) {
    err_type = PyExc_RuntimeError;
    err_msg += std::string(": ") + e.what();
  } catch (...) {
    err_type = PyExc_RuntimeError;
  }
  Py_BLOCK_THREADS
  if (err_type) {
    PyErr_SetString(err_type, err_msg.c_str());
    return nullptr;
  }
  return Clif_PyObjFrom(std::move(ret0), {});
}

// Implicit cast this as ::pycocotools::COCOevalBase*
static PyObject* as_pycocotools_COCOevalBase(PyObject* self) {
  ::pycocotools::COCOevalBase* p = ::clif::python::Get(reinterpret_cast<wrapper*>(self)->cpp);
  if (p == nullptr) return nullptr;
  return PyCapsule_New(p, "::pycocotools::COCOevalBase", nullptr);
}

static PyMethodDef MethodsStaticAlloc[] = {
  {"__init__", (PyCFunction)wrapCOCOeval_as___init__, METH_VARARGS | METH_KEYWORDS, "__init__(coco_gt:COCO, coco_dt:COCO, iou_type:str)\n  Calls C++ function\n  void ::pycocotools::COCOeval::COCOeval(::pycocotools::COCO, ::pycocotools::COCO, ::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>>)"},
  {"Evaluate", (PyCFunction)wrapEvaluate, METH_NOARGS, "Evaluate()\n  Calls C++ function\n  void ::pycocotools::COCOevalBase::Evaluate()"},
  {"Accumulate", (PyCFunction)wrapAccumulate, METH_NOARGS, "Accumulate()\n  Calls C++ function\n  void ::pycocotools::COCOevalBase::Accumulate()"},
  {"Summarize", (PyCFunction)wrapSummarize, METH_NOARGS, "Summarize()\n  Calls C++ function\n  void ::pycocotools::COCOevalBase::Summarize()"},
  {"GetStats", (PyCFunction)wrapGetStats, METH_NOARGS, "GetStats() -> list<float>\n  Calls C++ function\n  ::std::vector<float> ::pycocotools::COCOevalBase::GetStats()"},
  {"as_pycocotools_COCOevalBase", (PyCFunction)as_pycocotools_COCOevalBase, METH_NOARGS, "Upcast to ::pycocotools::COCOevalBase*"},
  {"__reduce_ex__", (PyCFunction)::clif::ReduceExImpl, METH_VARARGS | METH_KEYWORDS, "Helper for pickle."},
  {}
};

// COCOeval __init__
static int _ctor(PyObject* self, PyObject* args, PyObject* kw);

// COCOeval __new__
static PyObject* _new(PyTypeObject* type, Py_ssize_t nitems);

// COCOeval __del__
static void _dtor(PyObject* self) {
  if (reinterpret_cast<wrapper*>(self)->weakrefs) {
    PyObject_ClearWeakRefs(self);
  }
  Py_BEGIN_ALLOW_THREADS
  reinterpret_cast<wrapper*>(self)->cpp.Destruct();
  Py_END_ALLOW_THREADS
  Py_TYPE(self)->tp_free(self);
}

static void _del(void* self) {
  delete reinterpret_cast<wrapper*>(self);
}

PyTypeObject* wrapper_Type = nullptr;

static PyTypeObject* _build_heap_type() {
  PyHeapTypeObject *heap_type =
      (PyHeapTypeObject *) PyType_Type.tp_alloc(&PyType_Type, 0);
  if (!heap_type)
    return nullptr;
  heap_type->ht_qualname = (PyObject *) PyUnicode_FromString(
      "COCOeval");
  Py_INCREF(heap_type->ht_qualname);
  heap_type->ht_name = heap_type->ht_qualname;
  PyTypeObject *ty = &heap_type->ht_type;
  ty->tp_as_number = &heap_type->as_number;
  ty->tp_as_sequence = &heap_type->as_sequence;
  ty->tp_as_mapping = &heap_type->as_mapping;
#if PY_VERSION_HEX >= 0x03050000
  ty->tp_as_async = &heap_type->as_async;
#endif
  ty->tp_name = "pycocotools.python.coco.COCOeval";
  ty->tp_basicsize = sizeof(wrapper);
  ty->tp_dealloc = _dtor;
  ty->tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE;
  ty->tp_doc = "CLIF wrapper for ::pycocotools::COCOeval";
  ty->tp_methods = MethodsStaticAlloc;
  ty->tp_init = _ctor;
  ty->tp_alloc = _new;
  ty->tp_new = PyType_GenericNew;
  ty->tp_free = _del;
  ty->tp_weaklistoffset = offsetof(wrapper, weakrefs);
  return ty;
}

static int _ctor(PyObject* self, PyObject* args, PyObject* kw) {
  PyObject* init = wrapCOCOeval_as___init__(self, args, kw);
  Py_XDECREF(init);
  return init? 0: -1;
}

static PyObject* _new(PyTypeObject* type, Py_ssize_t nitems) {
  DCHECK(nitems == 0);
  wrapper* wobj = new wrapper;
  PyObject* self = reinterpret_cast<PyObject*>(wobj);
  return PyObject_Init(self, wrapper_Type);
}

static ::pycocotools::COCOeval* ThisPtr(PyObject* py) {
  if (Py_TYPE(py) == wrapper_Type) {
    return ::clif::python::Get(reinterpret_cast<wrapper*>(py)->cpp);
  }
  PyObject* base = PyObject_CallMethod(py, "as_pycocotools_COCOeval", nullptr);
  if (base == nullptr) {
    PyErr_Clear();
  } else {
    if (PyCapsule_CheckExact(base)) {
      void* p = PyCapsule_GetPointer(base, "::pycocotools::COCOeval");
      if (!PyErr_Occurred()) {
        ::pycocotools::COCOeval* c = static_cast<::pycocotools::COCOeval*>(p);
        Py_DECREF(base);
        return c;
      }
    }
    Py_DECREF(base);
  }
  if (PyObject_IsInstance(py, reinterpret_cast<PyObject*>(wrapper_Type))) {
    if (!base) {
      return ::clif::python::Get(reinterpret_cast<wrapper*>(py)->cpp);
    }
    PyErr_Format(PyExc_ValueError, "can't convert %s %s to ::pycocotools::COCOeval*", ClassName(py), ClassType(py));
  } else {
    PyErr_Format(PyExc_TypeError, "expecting %s instance, got %s %s", wrapper_Type->tp_name, ClassName(py), ClassType(py));
  }
  return nullptr;
}

}  // namespace pyCOCOeval

// Initialize module

bool Ready() {
  pyCOCO::wrapper_Type =
  pyCOCO::_build_heap_type();
  if (PyType_Ready(pyCOCO::wrapper_Type) < 0) return false;
  PyObject *modname = PyUnicode_FromString(ThisModuleName);
  if (modname == nullptr) return false;
  PyObject_SetAttrString((PyObject *) pyCOCO::wrapper_Type, "__module__", modname);
  Py_INCREF(pyCOCO::wrapper_Type);  // For PyModule_AddObject to steal.
  pyCOCOeval::wrapper_Type =
  pyCOCOeval::_build_heap_type();
  if (PyType_Ready(pyCOCOeval::wrapper_Type) < 0) return false;
  PyObject_SetAttrString((PyObject *) pyCOCOeval::wrapper_Type, "__module__", modname);
  Py_INCREF(pyCOCOeval::wrapper_Type);  // For PyModule_AddObject to steal.
  return true;
}

static struct PyModuleDef Module = {
  PyModuleDef_HEAD_INIT,
  ThisModuleName,
  "CLIF-generated module for /tmp/clif/examples/pycocotools/python/coco.clif", // module doc
  -1,  // module keeps state in global variables
  nullptr,
  nullptr,  // m_slots a.k.a. m_reload
  nullptr,  // m_traverse
  ClearImportCache  // m_clear
};

PyObject* Init() {
  PyObject* module = PyModule_Create(&Module);
  if (!module) return nullptr;
  PyEval_InitThreads();
  if (PyModule_AddObject(module, "COCO", reinterpret_cast<PyObject*>(pyCOCO::wrapper_Type)) < 0) goto err;
  if (PyModule_AddObject(module, "COCOeval", reinterpret_cast<PyObject*>(pyCOCOeval::wrapper_Type)) < 0) goto err;
  return module;
err:
  Py_DECREF(module);
  return nullptr;
}

}  // namespace pycocotools_python_coco_clifwrap

namespace pycocotools {
using namespace ::clif;
using ::clif::Clif_PyObjAs;
using ::clif::Clif_PyObjFrom;

// COCO to/from ::pycocotools::COCO conversion

bool Clif_PyObjAs(PyObject* py, ::pycocotools::COCO** c) {
  CHECK(c != nullptr);
  if (Py_None == py) {
    *c = nullptr;
    return true;
  }
  ::pycocotools::COCO* cpp = pycocotools_python_coco_clifwrap::pyCOCO::ThisPtr(py);
  if (cpp == nullptr) return false;
  *c = cpp;
  return true;
}

bool Clif_PyObjAs(PyObject* py, std::shared_ptr<::pycocotools::COCO>* c) {
  CHECK(c != nullptr);
  ::pycocotools::COCO* cpp = pycocotools_python_coco_clifwrap::pyCOCO::ThisPtr(py);
  if (cpp == nullptr) return false;
  *c = ::clif::MakeStdShared(reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCO::wrapper*>(py)->cpp, cpp);
  return true;
}

bool Clif_PyObjAs(PyObject* py, std::unique_ptr<::pycocotools::COCO>* c) {
  CHECK(c != nullptr);
  ::pycocotools::COCO* cpp = pycocotools_python_coco_clifwrap::pyCOCO::ThisPtr(py);
  if (cpp == nullptr) return false;
  if (!reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCO::wrapper*>(py)->cpp.Detach()) {
    PyErr_SetString(PyExc_ValueError, "Cannot convert COCO instance to std::unique_ptr.");
    return false;
  }
  c->reset(cpp);
  return true;
}

bool Clif_PyObjAs(PyObject* py, ::pycocotools::COCO* c) {
  CHECK(c != nullptr);
  ::pycocotools::COCO* cpp = pycocotools_python_coco_clifwrap::pyCOCO::ThisPtr(py);
  if (cpp == nullptr) return false;
  *c = *cpp;
  return true;
}

PyObject* Clif_PyObjFrom(::pycocotools::COCO* c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCO) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  if (c == nullptr) Py_RETURN_NONE;
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCO::wrapper*>(py)->cpp = ::clif::Instance<::pycocotools::COCO>(c, ::clif::UnOwnedResource());
  return py;
}

PyObject* Clif_PyObjFrom(std::shared_ptr<::pycocotools::COCO> c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCO) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  if (c == nullptr) Py_RETURN_NONE;
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCO::wrapper*>(py)->cpp = ::clif::Instance<::pycocotools::COCO>(c);
  return py;
}

PyObject* Clif_PyObjFrom(std::unique_ptr<::pycocotools::COCO> c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCO) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  if (c == nullptr) Py_RETURN_NONE;
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCO::wrapper*>(py)->cpp = ::clif::Instance<::pycocotools::COCO>(std::move(c));
  return py;
}

PyObject* Clif_PyObjFrom(::pycocotools::COCO&& c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCO) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCO::wrapper*>(py)->cpp = ::clif::MakeShared<::pycocotools::COCO>(std::move(c));
  return py;
}

PyObject* Clif_PyObjFrom(const ::pycocotools::COCO& c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCO) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCO::wrapper*>(py)->cpp = ::clif::MakeShared<::pycocotools::COCO>(c);
  return py;
}

PyObject* Clif_PyObjFrom(const ::pycocotools::COCO* c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCO) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  if (c == nullptr) Py_RETURN_NONE;
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCO::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCO::wrapper*>(py)->cpp = ::clif::MakeShared<::pycocotools::COCO>(*c);
  return py;
}

// COCOeval to/from ::pycocotools::COCOeval conversion

bool Clif_PyObjAs(PyObject* py, ::pycocotools::COCOeval** c) {
  CHECK(c != nullptr);
  if (Py_None == py) {
    *c = nullptr;
    return true;
  }
  ::pycocotools::COCOeval* cpp = pycocotools_python_coco_clifwrap::pyCOCOeval::ThisPtr(py);
  if (cpp == nullptr) return false;
  *c = cpp;
  return true;
}

bool Clif_PyObjAs(PyObject* py, std::shared_ptr<::pycocotools::COCOeval>* c) {
  CHECK(c != nullptr);
  ::pycocotools::COCOeval* cpp = pycocotools_python_coco_clifwrap::pyCOCOeval::ThisPtr(py);
  if (cpp == nullptr) return false;
  *c = ::clif::MakeStdShared(reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper*>(py)->cpp, cpp);
  return true;
}

bool Clif_PyObjAs(PyObject* py, std::unique_ptr<::pycocotools::COCOeval>* c) {
  CHECK(c != nullptr);
  ::pycocotools::COCOeval* cpp = pycocotools_python_coco_clifwrap::pyCOCOeval::ThisPtr(py);
  if (cpp == nullptr) return false;
  if (!reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper*>(py)->cpp.Detach()) {
    PyErr_SetString(PyExc_ValueError, "Cannot convert COCOeval instance to std::unique_ptr.");
    return false;
  }
  c->reset(cpp);
  return true;
}

bool Clif_PyObjAs(PyObject* py, ::pycocotools::COCOeval* c) {
  CHECK(c != nullptr);
  ::pycocotools::COCOeval* cpp = pycocotools_python_coco_clifwrap::pyCOCOeval::ThisPtr(py);
  if (cpp == nullptr) return false;
  *c = *cpp;
  return true;
}

PyObject* Clif_PyObjFrom(::pycocotools::COCOeval* c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCOeval) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  if (c == nullptr) Py_RETURN_NONE;
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper*>(py)->cpp = ::clif::Instance<::pycocotools::COCOeval>(c, ::clif::UnOwnedResource());
  return py;
}

PyObject* Clif_PyObjFrom(std::shared_ptr<::pycocotools::COCOeval> c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCOeval) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  if (c == nullptr) Py_RETURN_NONE;
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper*>(py)->cpp = ::clif::Instance<::pycocotools::COCOeval>(c);
  return py;
}

PyObject* Clif_PyObjFrom(std::unique_ptr<::pycocotools::COCOeval> c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCOeval) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  if (c == nullptr) Py_RETURN_NONE;
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper*>(py)->cpp = ::clif::Instance<::pycocotools::COCOeval>(std::move(c));
  return py;
}

PyObject* Clif_PyObjFrom(::pycocotools::COCOeval&& c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCOeval) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper*>(py)->cpp = ::clif::MakeShared<::pycocotools::COCOeval>(std::move(c));
  return py;
}

PyObject* Clif_PyObjFrom(const ::pycocotools::COCOeval& c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCOeval) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper*>(py)->cpp = ::clif::MakeShared<::pycocotools::COCOeval>(c);
  return py;
}

PyObject* Clif_PyObjFrom(const ::pycocotools::COCOeval* c, py::PostConv unused) {
  CHECK(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type != nullptr) <<
    "---> Function Clif_PyObjFrom(::pycocotools::COCOeval) called before " <<
    pycocotools_python_coco_clifwrap::ThisModuleName  <<
    " was imported from Python.";
  if (c == nullptr) Py_RETURN_NONE;
  PyObject* py = PyType_GenericNew(pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper_Type, NULL, NULL);
  reinterpret_cast<pycocotools_python_coco_clifwrap::pyCOCOeval::wrapper*>(py)->cpp = ::clif::MakeShared<::pycocotools::COCOeval>(*c);
  return py;
}

}  // namespace pycocotools
