#include "Python.h"
#define PYSAMPLE_MODULE
#include "pysample.h"
#include "embed.h"

/* int gcd(int, int) */
static PyObject* py_gcd(PyObject* self, PyObject* args) 
{
	int x, y, result;
	if (!PyArg_ParseTuple(args, "ii", &x, &y)) {
		return NULL;
	}
	result = gcd(x, y);
	return Py_BuildValue("i", result);
}


/* int in_mandel(double, double, int) */
static PyObject* py_in_mandel(PyObject* self, PyObject* args)
{
	double x0, y0;
	int n;
	int result;

	if (!PyArg_ParseTuple(args, "ddi", &x0, &y0, &n)) {
		return NULL;
	}
	result = in_mandel(x0, y0, n);
	return Py_BuildValue("i", result);
}


/* int divide(int, int, int*) */
static PyObject* py_divide(PyObject* self, PyObject* args)
{
	int a, b, remainder;
	int quot;

	if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
		return NULL;
	}

	quot = divide(a, b, &remainder);
	return Py_BuildValue("(ii)", quot, remainder);
}


/* double avg(double*, int) */
static PyObject* py_avg(PyObject* self, PyObject* args)
{
    PyObject* bufobj;
    Py_buffer view;
    double result;

    if (!PyArg_ParseTuple(args, "O", &bufobj)) {
        return NULL;
    }

    if (PyObject_GetBuffer(bufobj, &view, PyBUF_ANY_CONTIGUOUS | PyBUF_FORMAT) == -1) {
        return NULL;
    }

    if (view.ndim != 1) {
        PyErr_SetString(PyExc_TypeError, "Expected a 1-dimensional array");
        PyBuffer_Release(&view);
        return NULL;
    }

    if (strcmp(view.format, "d") != 0) {
        PyErr_SetString(PyExc_TypeError, "Expected an array of doubles");
        PyBuffer_Release(&view);
        return NULL;
    }

    result = avg(view.buf, view.shape[0]);
    PyBuffer_Release(&view);
    return Py_BuildValue("d", result);
}

static void del_Point(PyObject *obj)
{
    printf("Deleting poing\n");
    free(PyCapsule_GetPointer(obj, "Point"));
}


static Point* PyPoint_AsPoint(PyObject* obj)
{
    return (Point*) PyCapsule_GetPointer(obj, "Point");
}


static PyObject* PyPoint_FromPoint(Point* p, int must_free)
{
    return PyCapsule_New(p, "Point", must_free ? del_Point : NULL);
}


static _PointAPIMethods _point_api = {
    PyPoint_AsPoint,
    PyPoint_FromPoint
};


static PyObject* py_Point(PyObject* self, PyObject* args)
{
    Point* p;
    double x, y;
    
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    p = (Point*) malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    return PyPoint_FromPoint(p, 1);
}


static PyObject* py_distance(PyObject* self, PyObject* args)
{
    Point* p1;
    Point* p2;
    PyObject* py_p1;
    PyObject* py_p2;
    double result;

    if (!PyArg_ParseTuple(args, "OO", &py_p1, &py_p2)) {
        return NULL;
    }

    if (!(p1 = PyPoint_AsPoint(py_p1))) {
        return NULL;
    }
    if (!(p2 = PyPoint_AsPoint(py_p2))) {
        return NULL;
    }

    result = distance(p1, p2);
    return Py_BuildValue("d", result);
}


PyObject* py_call_func(PyObject* self, PyObject* args)
{
    PyObject* func;
    double x, y;
    double result;

    if (!PyArg_ParseTuple(args, "Odd", &func, &x, &y)) {
        return NULL;
    }

    result = call_func(func, x, y);
    return Py_BuildValue("d", result);
}


/* Module method table */
static PyMethodDef SampleMethods[] = {
	{"gcd", py_gcd, METH_VARARGS, "Greatest common divisor"},
	{"in_mandel", py_in_mandel, METH_VARARGS, "Mandelbrot test"},
	{"divide", py_divide, METH_VARARGS, "Integer division"},
    {"avg", py_avg, METH_VARARGS, "Average"},
    {"Point", py_Point, METH_VARARGS, "struct Point"},
    {"distance", py_distance, METH_VARARGS, "Point distance"},
    {"call_func", py_call_func, METH_VARARGS, "Call python func from c"},
	{NULL, NULL, 0, NULL}
};


/* Module structure */
static struct PyModuleDef samplemodule = {
	PyModuleDef_HEAD_INIT,
	"sample",
	"A sample module",
	-1,
	SampleMethods
};


/* Module initialization function */
PyMODINIT_FUNC 
PyInit_sample(void) 
{
    PyObject* m;
    PyObject* py_point_api;

	m = PyModule_Create(&samplemodule);
    if (m == NULL)
        return NULL;

    /* Add the Point C API functions */
    py_point_api = PyCapsule_New((void*)&_point_api, "sample._point_api", NULL);
    if (py_point_api) {
        PyModule_AddObject(m, "_point_api", py_point_api);
    }
    return m;
}

