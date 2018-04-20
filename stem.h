#pragma once

#include "_python.h"
#include "interpreter.h"
#include "helpers.h"

namespace matplotlibcpp {
template<typename Numeric>
bool stem(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::map<std::string, std::string>& keywords)
{
    assert(x.size() == y.size());

    // using numpy arrays
    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);

    // construct positional args
    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, xarray);
    PyTuple_SetItem(args, 1, yarray);

    // construct keyword args
    PyObject* kwargs = helpers::to_dict(keywords);

    PyObject* res = PyObject_Call(
            detail::_interpreter::get().s_python_function_stem, args, kwargs);

    Py_DECREF(args);
    Py_DECREF(kwargs);
    if (res != nullptr)
        Py_DECREF(res);

    return res != nullptr;
}

template<typename NumericX, typename NumericY>
bool stem(const std::vector<NumericX>& x, const std::vector<NumericY>& y, const std::string& s = "")
{
    assert(x.size() == y.size());

    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);

    PyObject* pystring = PyString_FromString(s.c_str());

    PyObject* plot_args = PyTuple_New(3);
    PyTuple_SetItem(plot_args, 0, xarray);
    PyTuple_SetItem(plot_args, 1, yarray);
    PyTuple_SetItem(plot_args, 2, pystring);

    PyObject* res = PyObject_CallObject(
            detail::_interpreter::get().s_python_function_stem, plot_args);

    Py_DECREF(plot_args);
    if (res != nullptr)
        Py_DECREF(res);

    return res != nullptr;
}

template<typename Numeric>
bool stem(const std::vector<Numeric>& y, const std::string& format = "")
{
    std::vector<Numeric> x(y.size());
    for (size_t i = 0; i < x.size(); ++i) x.at(i) = static_cast<Numeric>(i);
    return stem(x, y, format);
}
} // end namespace matplotlibcpp
