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
} // end namespace matplotlibcpp
