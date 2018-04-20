#pragma once

#ifdef _DEBUG
    #ifdef _MSC_VER
        #undef _DEBUG
        #include <Python.h>
        #define _DEBUG
    #else
        #include <Python.h>
    #endif
#else
    #include <Python.h>
#endif

#ifndef WITHOUT_NUMPY
    #define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
    #include <numpy/arrayobject.h>
#endif // WITHOUT_NUMPY

#if PY_MAJOR_VERSION >= 3
    #define PyString_FromString PyUnicode_FromString
#endif
