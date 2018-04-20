#pragma once

#include "_python.h"
#include "interpreter.h"

namespace matplotlibcpp {
#ifndef WITHOUT_NUMPY
// Type selector for numpy array conversion
template <typename T> struct select_npy_type { const static NPY_TYPES type = NPY_NOTYPE; }; //Default
template <> struct select_npy_type<double> { const static NPY_TYPES type = NPY_DOUBLE; };
template <> struct select_npy_type<float> { const static NPY_TYPES type = NPY_FLOAT; };
template <> struct select_npy_type<bool> { const static NPY_TYPES type = NPY_BOOL; };
template <> struct select_npy_type<int8_t> { const static NPY_TYPES type = NPY_INT8; };
template <> struct select_npy_type<int16_t> { const static NPY_TYPES type = NPY_SHORT; };
template <> struct select_npy_type<int32_t> { const static NPY_TYPES type = NPY_INT; };
template <> struct select_npy_type<int64_t> { const static NPY_TYPES type = NPY_INT64; };
template <> struct select_npy_type<uint8_t> { const static NPY_TYPES type = NPY_UINT8; };
template <> struct select_npy_type<uint16_t> { const static NPY_TYPES type = NPY_USHORT; };
template <> struct select_npy_type<uint32_t> { const static NPY_TYPES type = NPY_ULONG; };
template <> struct select_npy_type<uint64_t> { const static NPY_TYPES type = NPY_UINT64; };

template<typename Numeric>
PyObject* get_array(const std::vector<Numeric>& v)
{
    detail::_interpreter::get();    //interpreter needs to be initialized for the numpy commands to work
    NPY_TYPES type = select_npy_type<Numeric>::type;
    if (type == NPY_NOTYPE)
    {
        std::vector<double> vd(v.size());
        npy_intp vsize = v.size();
        std::copy(v.begin(),v.end(),vd.begin());
        PyObject* varray = PyArray_SimpleNewFromData(1, &vsize, NPY_DOUBLE, (void*)(vd.data()));
        return varray;
    }

    npy_intp vsize = v.size();
    PyObject* varray = PyArray_SimpleNewFromData(1, &vsize, type, (void*)(v.data()));
    return varray;
}

#else // fallback if we don't have numpy: copy every element of the given vector

template<typename Numeric>
PyObject* get_array(const std::vector<Numeric>& v)
{
    PyObject* list = PyList_New(v.size());
    for(size_t i = 0; i < v.size(); ++i) {
        PyList_SetItem(list, i, PyFloat_FromDouble(v.at(i)));
    }
    return list;
}

#endif // WITHOUT_NUMPY

template<typename Numeric>
PyObject* get_array(const std::vector<Numeric>& v, size_t width, size_t height)
{
    assert(v.size() == width * height);

    PyObject* list = PyList_New(height);
    for(size_t i = 0; i < height; ++i) {
        PyObject* row = PyList_New(width);
        for(size_t j = 0u; j < width; ++j)
        {
            PyList_SetItem(row, j, PyFloat_FromDouble(v.at(i * width + j)));
        }
        PyList_SetItem(list, i, row);
    }
    return list;
}
} // end namespace matplotlibcpp
