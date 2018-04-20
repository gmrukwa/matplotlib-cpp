#pragma once

#include "_python.h"

namespace matplotlibcpp { namespace detail {

static std::string s_backend;

struct _interpreter {
    PyObject *s_python_function_show;
    PyObject *s_python_function_close;
    PyObject *s_python_function_draw;
    PyObject *s_python_function_pause;
    PyObject *s_python_function_save;
    PyObject *s_python_function_figure;
    PyObject *s_python_function_plot;
    PyObject *s_python_function_semilogx;
    PyObject *s_python_function_semilogy;
    PyObject *s_python_function_loglog;
    PyObject *s_python_function_fill_between;
    PyObject *s_python_function_hist;
    PyObject *s_python_function_subplot;
    PyObject *s_python_function_legend;
    PyObject *s_python_function_xlim;
    PyObject *s_python_function_ion;
    PyObject *s_python_function_ylim;
    PyObject *s_python_function_title;
    PyObject *s_python_function_axis;
    PyObject *s_python_function_xlabel;
    PyObject *s_python_function_ylabel;
    PyObject *s_python_function_grid;
    PyObject *s_python_function_clf;
    PyObject *s_python_function_errorbar;
    PyObject *s_python_function_annotate;
    PyObject *s_python_function_tight_layout;
    PyObject *s_python_empty_tuple;
    PyObject *s_python_function_stem;
    PyObject *s_python_function_xkcd;
    PyObject *s_python_function_imshow;

    /* For now, _interpreter is implemented as a singleton since its currently not possible to have
       multiple independent embedded python interpreters without patching the python source code
       or starting a separate process for each.
        http://bytes.com/topic/python/answers/793370-multiple-independent-python-interpreters-c-c-program
       */

    static _interpreter& get() {
        static _interpreter ctx;
        return ctx;
    }

private:

#ifndef WITHOUT_NUMPY
#  if PY_MAJOR_VERSION >= 3

    void *import_numpy() {
        import_array(); // initialize C-API
        return NULL;
    }

#  else

    void import_numpy() {
        import_array(); // initialize C-API
    }

#  endif
#endif

    _interpreter() {

        // optional but recommended
#if PY_MAJOR_VERSION >= 3
        wchar_t name[] = L"plotting";
#else
        char name[] = "plotting";
#endif
        Py_SetProgramName(name);
        Py_Initialize();

#ifndef WITHOUT_NUMPY
        import_numpy(); // initialize numpy C-API
#endif

        PyObject* matplotlibname = PyString_FromString("matplotlib");
        PyObject* pyplotname = PyString_FromString("matplotlib.pyplot");
        PyObject* pylabname  = PyString_FromString("pylab");
        if (pyplotname == nullptr || pylabname == nullptr || matplotlibname == nullptr) {
            throw std::runtime_error("couldnt create string");
        }

        PyObject* matplotlib = PyImport_Import(matplotlibname);
        Py_DECREF(matplotlibname);
        if (matplotlib == nullptr) { throw std::runtime_error("Error loading module matplotlib!"); }

        // matplotlib.use() must be called *before* pylab, matplotlib.pyplot,
        // or matplotlib.backends is imported for the first time
        if (!s_backend.empty()) {
            PyObject_CallMethod(matplotlib, const_cast<char*>("use"), const_cast<char*>("s"), s_backend.c_str());
        }

        PyObject* pymod = PyImport_Import(pyplotname);
        Py_DECREF(pyplotname);
        if (pymod == nullptr) { throw std::runtime_error("Error loading module matplotlib.pyplot!"); }


        PyObject* pylabmod = PyImport_Import(pylabname);
        Py_DECREF(pylabname);
        if (pylabmod == nullptr) { throw std::runtime_error("Error loading module pylab!"); }

        s_python_function_show = PyObject_GetAttrString(pymod, "show");
        s_python_function_close = PyObject_GetAttrString(pymod, "close");
        s_python_function_draw = PyObject_GetAttrString(pymod, "draw");
        s_python_function_pause = PyObject_GetAttrString(pymod, "pause");
        s_python_function_figure = PyObject_GetAttrString(pymod, "figure");
        s_python_function_plot = PyObject_GetAttrString(pymod, "plot");
        s_python_function_semilogx = PyObject_GetAttrString(pymod, "semilogx");
        s_python_function_semilogy = PyObject_GetAttrString(pymod, "semilogy");
        s_python_function_loglog = PyObject_GetAttrString(pymod, "loglog");
        s_python_function_fill_between = PyObject_GetAttrString(pymod, "fill_between");
        s_python_function_hist = PyObject_GetAttrString(pymod,"hist");
        s_python_function_subplot = PyObject_GetAttrString(pymod, "subplot");
        s_python_function_legend = PyObject_GetAttrString(pymod, "legend");
        s_python_function_ylim = PyObject_GetAttrString(pymod, "ylim");
        s_python_function_title = PyObject_GetAttrString(pymod, "title");
        s_python_function_axis = PyObject_GetAttrString(pymod, "axis");
        s_python_function_xlabel = PyObject_GetAttrString(pymod, "xlabel");
        s_python_function_ylabel = PyObject_GetAttrString(pymod, "ylabel");
        s_python_function_grid = PyObject_GetAttrString(pymod, "grid");
        s_python_function_xlim = PyObject_GetAttrString(pymod, "xlim");
        s_python_function_ion = PyObject_GetAttrString(pymod, "ion");
        s_python_function_save = PyObject_GetAttrString(pylabmod, "savefig");
        s_python_function_annotate = PyObject_GetAttrString(pymod,"annotate");
        s_python_function_clf = PyObject_GetAttrString(pymod, "clf");
        s_python_function_errorbar = PyObject_GetAttrString(pymod, "errorbar");
        s_python_function_tight_layout = PyObject_GetAttrString(pymod, "tight_layout");
        s_python_function_stem = PyObject_GetAttrString(pymod, "stem");
        s_python_function_xkcd = PyObject_GetAttrString(pymod, "xkcd");
        s_python_function_imshow = PyObject_GetAttrString(pymod, "imshow");

        if(    s_python_function_show == nullptr
            || s_python_function_close == nullptr
            || s_python_function_draw == nullptr
            || s_python_function_pause == nullptr
            || s_python_function_figure == nullptr
            || s_python_function_plot == nullptr
            || s_python_function_semilogx == nullptr
            || s_python_function_semilogy == nullptr
            || s_python_function_loglog == nullptr
            || s_python_function_fill_between == nullptr
            || s_python_function_subplot == nullptr
            || s_python_function_legend == nullptr
            || s_python_function_ylim == nullptr
            || s_python_function_title == nullptr
            || s_python_function_axis == nullptr
            || s_python_function_xlabel == nullptr
            || s_python_function_ylabel == nullptr
            || s_python_function_grid == nullptr
            || s_python_function_xlim == nullptr
            || s_python_function_ion == nullptr
            || s_python_function_save == nullptr
            || s_python_function_clf == nullptr
            || s_python_function_annotate == nullptr
            || s_python_function_errorbar == nullptr
            || s_python_function_errorbar == nullptr
            || s_python_function_tight_layout == nullptr
            || s_python_function_stem == nullptr
            || s_python_function_xkcd == nullptr
            || s_python_function_imshow == nullptr
        ) { throw std::runtime_error("Couldn't find required function!"); }

        if (   PyFunction_Check(s_python_function_show) == 0
            || PyFunction_Check(s_python_function_close) == 0
            || PyFunction_Check(s_python_function_draw) == 0
            || PyFunction_Check(s_python_function_pause) == 0
            || PyFunction_Check(s_python_function_figure) == 0
            || PyFunction_Check(s_python_function_plot) == 0
            || PyFunction_Check(s_python_function_semilogx) == 0
            || PyFunction_Check(s_python_function_semilogy) == 0
            || PyFunction_Check(s_python_function_loglog) == 0
            || PyFunction_Check(s_python_function_fill_between) == 0
            || PyFunction_Check(s_python_function_subplot) == 0
            || PyFunction_Check(s_python_function_legend) == 0
            || PyFunction_Check(s_python_function_annotate) == 0
            || PyFunction_Check(s_python_function_ylim) == 0
            || PyFunction_Check(s_python_function_title) == 0
            || PyFunction_Check(s_python_function_axis) == 0
            || PyFunction_Check(s_python_function_xlabel) == 0
            || PyFunction_Check(s_python_function_ylabel) == 0
            || PyFunction_Check(s_python_function_grid) == 0
            || PyFunction_Check(s_python_function_xlim) == 0
            || PyFunction_Check(s_python_function_ion) == 0
            || PyFunction_Check(s_python_function_save) == 0
            || PyFunction_Check(s_python_function_clf) == 0
            || PyFunction_Check(s_python_function_tight_layout) == 0
            || PyFunction_Check(s_python_function_errorbar) == 0
            || PyFunction_Check(s_python_function_stem) == 0
            || PyFunction_Check(s_python_function_xkcd) == 0
            || PyFunction_Check(s_python_function_imshow) == 0
        ) { throw std::runtime_error("Python object is unexpectedly not a PyFunction."); }

        s_python_empty_tuple = PyTuple_New(0);
    }

    ~_interpreter() {
        Py_Finalize();
    }
};

} // end namespace detail

// must be called before the first regular call to matplotlib to have any effect
inline void backend(const std::string& name)
{
    detail::s_backend = name;
}
} // end namespace matplotlibcpp
