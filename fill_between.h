#pragma once

#include "_python.h"
#include "interpreter.h"
#include "helpers.h"

namespace matplotlibcpp {
template< typename Numeric >
bool fill_between(const std::vector<Numeric>& x, const std::vector<Numeric>& y1, const std::vector<Numeric>& y2, const std::map<std::string, std::string>& keywords)
{
    assert(x.size() == y1.size());
    assert(x.size() == y2.size());

    // using numpy arrays
    PyObject* xarray = get_array(x);
    PyObject* y1array = get_array(y1);
    PyObject* y2array = get_array(y2);

    // construct positional args
    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, xarray);
    PyTuple_SetItem(args, 1, y1array);
    PyTuple_SetItem(args, 2, y2array);

    // construct keyword args
    PyObject* kwargs = helpers::to_dict(keywords);

    PyObject* res = PyObject_Call(detail::_interpreter::get().s_python_function_fill_between, args, kwargs);

    Py_DECREF(args);
    Py_DECREF(kwargs);
    if(res != nullptr) Py_DECREF(res);

    return res != nullptr;
}
} // end namespace matplotlibcpp
