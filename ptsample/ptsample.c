#include <stdio.h>
#include "pysample.h"

static PyObject* py_print_point(PyObject* self, PyObject* args)
{
    Point* p;
    PyObject* py_obj;

    if (!PyArg_ParseTuple(args, "O", &py_obj)) {
        printf("Arguements parse error.\n");
        return NULL;
    }
   
    if ((p = PyPoint_AsPoint(py_obj)) == NULL) {
        printf("AsPoint error.\n");
        return NULL;
    }

    printf("p->x=%lf, p->y=%lf\n", p->x, p->y);
    return Py_BuildValue("");
}


static PyMethodDef PtMethods[] = {
    {"print_point", py_print_point, METH_VARARGS, "Show Point structure"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef ptmodule = {
    PyModuleDef_HEAD_INIT,
    "pt",
    "A pt module",
    -1,
    PtMethods
};

PyMODINIT_FUNC
PyInit_pt(void)
{
  PyObject* m;
  m = PyModule_Create(&ptmodule);
  if (m == NULL)
      return NULL;

  if (!import_sample()) {
      return NULL;
  }
  return m;
}
