#pragma once

#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <stdint.h> // <cstdint> requires c++11 support

#if __cplusplus > 199711L || _MSC_VER > 1800
#  include <functional>
#endif

#include "_python.h"
#include "interpreter.h"
#include "helpers.h"
#include "annotate.h"
#include "_numpy.h"
#include "plot.h"
#include "stem.h"
#include "fill_between.h"
#include "hist.h"


namespace matplotlibcpp {
template< typename Numeric>
bool named_hist(std::string label,const std::vector<Numeric>& y, long bins=10, std::string color="b", double alpha=1.0)
{
    PyObject* yarray = get_array(y);

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "label", PyString_FromString(label.c_str()));
    PyDict_SetItemString(kwargs, "bins", PyLong_FromLong(bins));
    PyDict_SetItemString(kwargs, "color", PyString_FromString(color.c_str()));
    PyDict_SetItemString(kwargs, "alpha", PyFloat_FromDouble(alpha));


    PyObject* plot_args = PyTuple_New(1);
    PyTuple_SetItem(plot_args, 0, yarray);

    PyObject* res = PyObject_Call(detail::_interpreter::get().s_python_function_hist, plot_args, kwargs);

    Py_DECREF(plot_args);
    Py_DECREF(kwargs);
    if(res != nullptr) Py_DECREF(res);

    return res != nullptr;
}

template<typename NumericX, typename NumericY>
bool plot(const std::vector<NumericX>& x, const std::vector<NumericY>& y, const std::string& s = "")
{
    assert(x.size() == y.size());

    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);

    PyObject* pystring = PyString_FromString(s.c_str());

    PyObject* plot_args = PyTuple_New(3);
    PyTuple_SetItem(plot_args, 0, xarray);
    PyTuple_SetItem(plot_args, 1, yarray);
    PyTuple_SetItem(plot_args, 2, pystring);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_plot, plot_args);

    Py_DECREF(plot_args);
    if(res != nullptr) Py_DECREF(res);

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

template<typename NumericX, typename NumericY>
bool semilogx(const std::vector<NumericX>& x, const std::vector<NumericY>& y, const std::string& s = "")
{
    assert(x.size() == y.size());

    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);

    PyObject* pystring = PyString_FromString(s.c_str());

    PyObject* plot_args = PyTuple_New(3);
    PyTuple_SetItem(plot_args, 0, xarray);
    PyTuple_SetItem(plot_args, 1, yarray);
    PyTuple_SetItem(plot_args, 2, pystring);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_semilogx, plot_args);

    Py_DECREF(plot_args);
    if(res != nullptr) Py_DECREF(res);

    return res != nullptr;
}

template<typename NumericX, typename NumericY>
bool semilogy(const std::vector<NumericX>& x, const std::vector<NumericY>& y, const std::string& s = "")
{
    assert(x.size() == y.size());

    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);

    PyObject* pystring = PyString_FromString(s.c_str());

    PyObject* plot_args = PyTuple_New(3);
    PyTuple_SetItem(plot_args, 0, xarray);
    PyTuple_SetItem(plot_args, 1, yarray);
    PyTuple_SetItem(plot_args, 2, pystring);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_semilogy, plot_args);

    Py_DECREF(plot_args);
    if(res != nullptr) Py_DECREF(res);

    return res != nullptr;
}

template<typename NumericX, typename NumericY>
bool loglog(const std::vector<NumericX>& x, const std::vector<NumericY>& y, const std::string& s = "")
{
    assert(x.size() == y.size());

    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);

    PyObject* pystring = PyString_FromString(s.c_str());

    PyObject* plot_args = PyTuple_New(3);
    PyTuple_SetItem(plot_args, 0, xarray);
    PyTuple_SetItem(plot_args, 1, yarray);
    PyTuple_SetItem(plot_args, 2, pystring);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_loglog, plot_args);

    Py_DECREF(plot_args);
    if(res != nullptr) Py_DECREF(res);

    return res != nullptr;
}

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

template<typename Numeric>
bool named_plot(const std::string& name, const std::vector<Numeric>& y, const std::string& format = "")
{
    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "label", PyString_FromString(name.c_str()));

    PyObject* yarray = get_array(y);

    PyObject* pystring = PyString_FromString(format.c_str());

    PyObject* plot_args = PyTuple_New(2);

    PyTuple_SetItem(plot_args, 0, yarray);
    PyTuple_SetItem(plot_args, 1, pystring);

    PyObject* res = PyObject_Call(detail::_interpreter::get().s_python_function_plot, plot_args, kwargs);

    Py_DECREF(kwargs);
    Py_DECREF(plot_args);
    if (res != nullptr) Py_DECREF(res);

    return res != nullptr;
}

template<typename Numeric>
bool named_plot(const std::string& name, const std::vector<Numeric>& x, const std::vector<Numeric>& y, const std::string& format = "")
{
    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "label", PyString_FromString(name.c_str()));

    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);

    PyObject* pystring = PyString_FromString(format.c_str());

    PyObject* plot_args = PyTuple_New(3);
    PyTuple_SetItem(plot_args, 0, xarray);
    PyTuple_SetItem(plot_args, 1, yarray);
    PyTuple_SetItem(plot_args, 2, pystring);

    PyObject* res = PyObject_Call(detail::_interpreter::get().s_python_function_plot, plot_args, kwargs);

    Py_DECREF(kwargs);
    Py_DECREF(plot_args);
    if (res != nullptr) Py_DECREF(res);

    return res != nullptr;
}

template<typename Numeric>
bool named_semilogx(const std::string& name, const std::vector<Numeric>& x, const std::vector<Numeric>& y, const std::string& format = "")
{
    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "label", PyString_FromString(name.c_str()));

    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);

    PyObject* pystring = PyString_FromString(format.c_str());

    PyObject* plot_args = PyTuple_New(3);
    PyTuple_SetItem(plot_args, 0, xarray);
    PyTuple_SetItem(plot_args, 1, yarray);
    PyTuple_SetItem(plot_args, 2, pystring);

    PyObject* res = PyObject_Call(detail::_interpreter::get().s_python_function_semilogx, plot_args, kwargs);

    Py_DECREF(kwargs);
    Py_DECREF(plot_args);
    if (res != nullptr) Py_DECREF(res);

    return res != nullptr;
}

template<typename Numeric>
bool named_semilogy(const std::string& name, const std::vector<Numeric>& x, const std::vector<Numeric>& y, const std::string& format = "")
{
    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "label", PyString_FromString(name.c_str()));

    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);

    PyObject* pystring = PyString_FromString(format.c_str());

    PyObject* plot_args = PyTuple_New(3);
    PyTuple_SetItem(plot_args, 0, xarray);
    PyTuple_SetItem(plot_args, 1, yarray);
    PyTuple_SetItem(plot_args, 2, pystring);

    PyObject* res = PyObject_Call(detail::_interpreter::get().s_python_function_semilogy, plot_args, kwargs);

    Py_DECREF(kwargs);
    Py_DECREF(plot_args);
    if (res != nullptr) Py_DECREF(res);

    return res != nullptr;
}

template<typename Numeric>
bool named_loglog(const std::string& name, const std::vector<Numeric>& x, const std::vector<Numeric>& y, const std::string& format = "")
{
    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "label", PyString_FromString(name.c_str()));

    PyObject* xarray = get_array(x);
    PyObject* yarray = get_array(y);

    PyObject* pystring = PyString_FromString(format.c_str());

    PyObject* plot_args = PyTuple_New(3);
    PyTuple_SetItem(plot_args, 0, xarray);
    PyTuple_SetItem(plot_args, 1, yarray);
    PyTuple_SetItem(plot_args, 2, pystring);

    PyObject* res = PyObject_Call(detail::_interpreter::get().s_python_function_loglog, plot_args, kwargs);

    Py_DECREF(kwargs);
    Py_DECREF(plot_args);
    if (res != nullptr) Py_DECREF(res);

    return res != nullptr;
}

template<typename Numeric>
bool plot(const std::vector<Numeric>& y, const std::string& format = "")
{
    std::vector<Numeric> x(y.size());
    for(size_t i=0; i<x.size(); ++i) x.at(i) = static_cast<Numeric>(i);
    return plot(x,y,format);
}

template<typename Numeric>
bool stem(const std::vector<Numeric>& y, const std::string& format = "")
{
    std::vector<Numeric> x(y.size());
    for (size_t i = 0; i < x.size(); ++i) x.at(i) = static_cast<Numeric>(i);
    return stem(x, y, format);
}

inline void figure()
{
    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_figure, detail::_interpreter::get().s_python_empty_tuple);
    if(!res) throw std::runtime_error("Call to figure() failed.");

    Py_DECREF(res);
}

inline void legend()
{
    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_legend, detail::_interpreter::get().s_python_empty_tuple);
    if(!res) throw std::runtime_error("Call to legend() failed.");

    Py_DECREF(res);
}

template<typename Numeric>
void ylim(Numeric left, Numeric right)
{
    PyObject* list = PyList_New(2);
    PyList_SetItem(list, 0, PyFloat_FromDouble(left));
    PyList_SetItem(list, 1, PyFloat_FromDouble(right));

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, list);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_ylim, args);
    if(!res) throw std::runtime_error("Call to ylim() failed.");

    Py_DECREF(args);
    Py_DECREF(res);
}

template<typename Numeric>
void xlim(Numeric left, Numeric right)
{
    PyObject* list = PyList_New(2);
    PyList_SetItem(list, 0, PyFloat_FromDouble(left));
    PyList_SetItem(list, 1, PyFloat_FromDouble(right));

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, list);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_xlim, args);
    if(res == nullptr) throw std::runtime_error("Call to xlim() failed.");

    Py_DECREF(args);
    Py_DECREF(res);
}


inline double* xlim()
{
    PyObject* args = PyTuple_New(0);
    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_xlim, args);
    PyObject* left = PyTuple_GetItem(res,0);
    PyObject* right = PyTuple_GetItem(res,1);

    double* arr = new double[2];
    arr[0] = PyFloat_AsDouble(left);
    arr[1] = PyFloat_AsDouble(right);

    if(res == nullptr) throw std::runtime_error("Call to xlim() failed.");

    Py_DECREF(res);
    return arr;
}


inline double* ylim()
{
    PyObject* args = PyTuple_New(0);
    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_ylim, args);
    PyObject* left = PyTuple_GetItem(res,0);
    PyObject* right = PyTuple_GetItem(res,1);

    double* arr = new double[2];
    arr[0] = PyFloat_AsDouble(left);
    arr[1] = PyFloat_AsDouble(right);

    if(res == nullptr) throw std::runtime_error("Call to ylim() failed.");

    Py_DECREF(res);
    return arr;
}

inline void subplot(long nrows, long ncols, long plot_number)
{
    // construct positional args
    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, PyFloat_FromDouble(nrows));
    PyTuple_SetItem(args, 1, PyFloat_FromDouble(ncols));
    PyTuple_SetItem(args, 2, PyFloat_FromDouble(plot_number));

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_subplot, args);
    if(res == nullptr) throw std::runtime_error("Call to subplot() failed.");

    Py_DECREF(args);
    Py_DECREF(res);
}

inline void title(const std::string &titlestr)
{
    PyObject* pytitlestr = PyString_FromString(titlestr.c_str());
    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, pytitlestr);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_title, args);
    if(res == nullptr) throw std::runtime_error("Call to title() failed.");

    Py_DECREF(args);
    Py_DECREF(res);
}

inline void axis(const std::string &axisstr)
{
    PyObject* str = PyString_FromString(axisstr.c_str());
    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, str);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_axis, args);
    if(res == nullptr) throw std::runtime_error("Call to title() failed.");

    Py_DECREF(args);
    Py_DECREF(res);
}

inline void xlabel(const std::string &str)
{
    PyObject* pystr = PyString_FromString(str.c_str());
    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, pystr);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_xlabel, args);
    if(res == nullptr) throw std::runtime_error("Call to xlabel() failed.");

    Py_DECREF(args);
    Py_DECREF(res);
}

inline void ylabel(const std::string &str)
{
    PyObject* pystr = PyString_FromString(str.c_str());
    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, pystr);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_ylabel, args);
    if(res == nullptr) throw std::runtime_error("Call to ylabel() failed.");

    Py_DECREF(args);
    Py_DECREF(res);
}

inline void grid(bool flag)
{
    PyObject* pyflag = flag ? Py_True : Py_False;
    Py_INCREF(pyflag);

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, pyflag);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_grid, args);
    if(res == nullptr) throw std::runtime_error("Call to grid() failed.");

    Py_DECREF(args);
    Py_DECREF(res);
}

inline void show(const bool block = true)
{
    PyObject* res;
    if(block)
    {
        res = PyObject_CallObject(
                detail::_interpreter::get().s_python_function_show,
                detail::_interpreter::get().s_python_empty_tuple);
    }
    else
    {
        PyObject *kwargs = PyDict_New();
        PyDict_SetItemString(kwargs, "block", Py_False);
        res = PyObject_Call( detail::_interpreter::get().s_python_function_show, detail::_interpreter::get().s_python_empty_tuple, kwargs);
	Py_DECREF(kwargs);
    }


    if (res == nullptr) throw std::runtime_error("Call to show() failed.");

    Py_DECREF(res);
}

inline void close()
{
    PyObject* res = PyObject_CallObject(
            detail::_interpreter::get().s_python_function_close,
            detail::_interpreter::get().s_python_empty_tuple);

    if (!res) throw std::runtime_error("Call to close() failed.");

    Py_DECREF(res);
}

inline void xkcd() {
    PyObject* res;
    PyObject *kwargs = PyDict_New();

    res = PyObject_Call(detail::_interpreter::get().s_python_function_xkcd,
            detail::_interpreter::get().s_python_empty_tuple, kwargs);

    Py_DECREF(kwargs);

    if (res == nullptr)
        throw std::runtime_error("Call to show() failed.");

    Py_DECREF(res);
}

inline void draw()
{
    PyObject* res = PyObject_CallObject(
        detail::_interpreter::get().s_python_function_draw,
        detail::_interpreter::get().s_python_empty_tuple);

    if (res == nullptr) throw std::runtime_error("Call to draw() failed.");

    Py_DECREF(res);
}

template<typename Numeric>
inline void pause(Numeric interval)
{
    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, PyFloat_FromDouble(interval));

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_pause, args);
    if(res == nullptr) throw std::runtime_error("Call to pause() failed.");

    Py_DECREF(args);
    Py_DECREF(res);
}

inline void save(const std::string& filename)
{
    PyObject* pyfilename = PyString_FromString(filename.c_str());

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, pyfilename);

    PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_save, args);
    if (res == nullptr) throw std::runtime_error("Call to save() failed.");

    Py_DECREF(args);
    Py_DECREF(res);
}

inline void clf() {
    PyObject *res = PyObject_CallObject(
        detail::_interpreter::get().s_python_function_clf,
        detail::_interpreter::get().s_python_empty_tuple);

    if (res == nullptr) throw std::runtime_error("Call to clf() failed.");

    Py_DECREF(res);
}

    inline void ion() {
    PyObject *res = PyObject_CallObject(
        detail::_interpreter::get().s_python_function_ion,
        detail::_interpreter::get().s_python_empty_tuple);

    if (res == nullptr) throw std::runtime_error("Call to ion() failed.");

    Py_DECREF(res);
}

// Actually, is there any reason not to call this automatically for every plot?
inline void tight_layout() {
    PyObject *res = PyObject_CallObject(
        detail::_interpreter::get().s_python_function_tight_layout,
        detail::_interpreter::get().s_python_empty_tuple);

    if (res == nullptr) throw std::runtime_error("Call to tight_layout() failed.");

    Py_DECREF(res);
}

#if __cplusplus > 199711L || _MSC_VER > 1800
// C++11-exclusive content starts here (variadic plot() and initializer list support)

namespace detail {

template<typename T>
using is_function = typename std::is_function<std::remove_pointer<std::remove_reference<T>>>::type;

template<bool obj, typename T>
struct is_callable_impl;

template<typename T>
struct is_callable_impl<false, T>
{
    typedef is_function<T> type;
}; // a non-object is callable iff it is a function

template<typename T>
struct is_callable_impl<true, T>
{
    struct Fallback { void operator()(); };
    struct Derived : T, Fallback { };

    template<typename U, U> struct Check;

    template<typename U>
    static std::true_type test( ... ); // use a variadic function to make sure (1) it accepts everything and (2) its always the worst match

    template<typename U>
    static std::false_type test( Check<void(Fallback::*)(), &U::operator()>* );

public:
    typedef decltype(test<Derived>(nullptr)) type;
    typedef decltype(&Fallback::operator()) dtype;
    static constexpr bool value = type::value;
}; // an object is callable iff it defines operator()

template<typename T>
struct is_callable
{
    // dispatch to is_callable_impl<true, T> or is_callable_impl<false, T> depending on whether T is of class type or not
    typedef typename is_callable_impl<std::is_class<T>::value, T>::type type;
};

template<typename IsYDataCallable>
struct plot_impl { };

template<>
struct plot_impl<std::false_type>
{
    template<typename IterableX, typename IterableY>
    bool operator()(const IterableX& x, const IterableY& y, const std::string& format)
    {
        // 2-phase lookup for distance, begin, end
        using std::distance;
        using std::begin;
        using std::end;

        auto xs = distance(begin(x), end(x));
        auto ys = distance(begin(y), end(y));
        assert(xs == ys && "x and y data must have the same number of elements!");

        PyObject* xlist = PyList_New(xs);
        PyObject* ylist = PyList_New(ys);
        PyObject* pystring = PyString_FromString(format.c_str());

        auto itx = begin(x), ity = begin(y);
        for(size_t i = 0; i < static_cast<size_t>(xs); ++i) {
            PyList_SetItem(xlist, i, PyFloat_FromDouble(*itx++));
            PyList_SetItem(ylist, i, PyFloat_FromDouble(*ity++));
        }

        PyObject* plot_args = PyTuple_New(3);
        PyTuple_SetItem(plot_args, 0, xlist);
        PyTuple_SetItem(plot_args, 1, ylist);
        PyTuple_SetItem(plot_args, 2, pystring);

        PyObject* res = PyObject_CallObject(detail::_interpreter::get().s_python_function_plot, plot_args);

        Py_DECREF(plot_args);
        if(res != nullptr) Py_DECREF(res);

        return res != nullptr;
    }
};

template<>
struct plot_impl<std::true_type>
{
    template<typename Iterable, typename Callable>
    bool operator()(const Iterable& ticks, const Callable& f, const std::string& format)
    {
        if(begin(ticks) == end(ticks)) return true;

        // We could use additional meta-programming to deduce the correct element type of y,
        // but all values have to be convertible to double anyways
        std::vector<double> y;
        for(auto x : ticks) y.push_back(f(x));
        return plot_impl<std::false_type>()(ticks,y,format);
    }
};

} // end namespace detail

// recursion stop for the above
template<typename... Args>
bool plot() { return true; }

template<typename A, typename B, typename... Args>
bool plot(const A& a, const B& b, const std::string& format, Args... args)
{
    return detail::plot_impl<typename detail::is_callable<B>::type>()(a,b,format) && plot(args...);
}

/*
 * This group of plot() functions is needed to support initializer lists, i.e. calling
 *    plot( {1,2,3,4} )
 */
inline bool plot(const std::vector<double>& x, const std::vector<double>& y, const std::string& format = "") {
    return plot<double,double>(x,y,format);
}

inline bool plot(const std::vector<double>& y, const std::string& format = "") {
    return plot<double>(y,format);
}

inline bool plot(const std::vector<double>& x, const std::vector<double>& y, const std::map<std::string, std::string>& keywords) {
    return plot<double>(x,y,keywords);
}

#endif

} // end namespace matplotlibcpp
