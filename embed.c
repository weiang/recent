/*************************************************************************
	> File Name: embed.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2015年08月01日 星期六 19时29分03秒
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include "embed.h"

double call_func(PyObject* func, double x, double y)
{
    PyObject* args;
    PyObject* kwargs;
    PyObject* result = NULL;
    double retval;

    /* Own GIL */
    PyGILState_STATE state = PyGILState_Ensure();
    
    if (!PyCallable_Check(func)) {
        fprintf(stderr, "call_func: expected a callable\n");
        goto fail;
    }

    args = Py_BuildValue("(dd)", x, y);
    kwargs = NULL;

    result = PyObject_Call(func, args, kwargs);
    Py_DECREF(args);
    Py_XDECREF(kwargs);

    if (PyErr_Occurred()) {
        PyErr_Print();
        goto fail;
    }

    if (!PyFloat_Check(result)) {
        fprintf(stderr, "call_func: callable didn't return a float");
        goto fail;
    }

    retval = PyFloat_AsDouble(result);
    Py_DECREF(result);
    PyGILState_Release(state);
    return retval;

fail:
    Py_XDECREF(result);
    PyGILState_Release(state);
    abort();
}

