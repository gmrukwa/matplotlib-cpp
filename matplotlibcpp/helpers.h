#pragma once

#include "_python.h"

namespace matplotlibcpp {namespace helpers {
PyObject* to_dict(const std::map<std::string, std::string>& some_dict)
{
    PyObject* python_dict = PyDict_New();
    for (std::map<std::string, std::string>::const_iterator it = some_dict.begin(); it != some_dict.end(); ++it)
    {
        auto key = PyUnicode_FromString(it->first.c_str());
        auto value = PyUnicode_FromString(it->second.c_str());
        PyDict_SetItem(python_dict, key, value);
        Py_DECREF(key);
        Py_DECREF(value);
    }
    return python_dict;
}
}} // end namespace matplotlibcpp::helpers
