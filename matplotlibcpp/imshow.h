#pragma once

#include "_python.h"
#include "interpreter.h"
#include "_numpy.h"
#include "helpers.h"

namespace matplotlibcpp {
template<typename Numeric>
bool imshow(const std::vector<Numeric>& values, size_t width, size_t height, const std::string& cmap = "")
{
    PyObject* matrix = get_array(values, width, height);

    PyObject* colormap;
    if (cmap == "")
    {
        colormap = Py_None;
    }
    else
    {
        colormap = PyString_FromString(cmap.c_str());
    }

    PyObject* plot_args = PyTuple_New(2);
    PyTuple_SetItem(plot_args, 0, matrix);
    PyTuple_SetItem(plot_args, 1, colormap);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_imshow, plot_args);

    Py_DECREF(plot_args);
    if(res != nullptr) Py_DECREF(res);

    return res != nullptr;
}

template<typename Numeric>
bool named_imshow(const std::string& name, const std::vector<Numeric>& values, size_t width, size_t height, const std::string& cmap = "")
{
    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "label", PyString_FromString(name.c_str()));

    PyObject* matrix = get_array(values, width, height);

    PyObject* colormap;
    if (cmap == "")
    {
        colormap = Py_None;
    }
    else
    {
        colormap = PyString_FromString(cmap.c_str());
    }

    PyObject* plot_args = PyTuple_New(2);
    PyTuple_SetItem(plot_args, 0, matrix);
    PyTuple_SetItem(plot_args, 1, colormap);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_imshow, plot_args, kwargs);

    Py_DECREF(plot_args);
    Py_DECREF(kwargs);
    if(res != nullptr) Py_DECREF(res);

    return res != nullptr;
}
}
