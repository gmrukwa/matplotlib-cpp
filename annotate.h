#pragma once

#include "_python.h"
#include "interpreter.h"

namespace matplotlibcpp {
inline bool annotate(std::string annotation, double x, double y)
{
    PyObject * xy = PyTuple_New(2);
    PyObject * str = PyString_FromString(annotation.c_str());

    PyTuple_SetItem(xy,0,PyFloat_FromDouble(x));
    PyTuple_SetItem(xy,1,PyFloat_FromDouble(y));

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "xy", xy);

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, str);

    PyObject* res = PyObject_Call(detail::_interpreter::get().s_python_function_annotate, args, kwargs);

    Py_DECREF(args);
    Py_DECREF(kwargs);

    if(res != nullptr) Py_DECREF(res);

    return res != nullptr;
}
} // end namespace matplotlibcpp
