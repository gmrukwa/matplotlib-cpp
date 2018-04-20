#pragma once

#include "_python.h"
#include "interpreter.h"
#include "helpers.h"

namespace matplotlibcpp {
template<typename NumericX, typename NumericY>
bool errorbar(const std::vector<NumericX> &x, const std::vector<NumericY> &y, const std::vector<NumericX> &yerr, const std::string &s = "")
{
    assert(x.size() == y.size());

    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);
    PyObject* yerrarray = get_array(yerr);

    PyObject *kwargs = PyDict_New();

    PyDict_SetItemString(kwargs, "yerr", yerrarray);

    PyObject *pystring = PyString_FromString(s.c_str());

    PyObject *plot_args = PyTuple_New(2);
    PyTuple_SetItem(plot_args, 0, xarray);
    PyTuple_SetItem(plot_args, 1, yarray);

    PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_errorbar, plot_args, kwargs);

    Py_DECREF(kwargs);
    Py_DECREF(plot_args);

    if (res != nullptr)
        Py_DECREF(res);
    else
        throw std::runtime_error("Call to errorbar() failed.");

    return res != nullptr;
}
} // end namespace matplotlibcpp
