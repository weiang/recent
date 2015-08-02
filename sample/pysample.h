#include "Python.h"
#include "sample.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* Public API Table */
typedef struct {
    Point* (*aspoint)(PyObject*);
    PyObject* (*frompoint)(Point*, int);
    void (*delpoint)(PyObject*);
} _PointAPIMethods;


#ifndef PYSAMPLE_MODULE
static _PointAPIMethods* _point_api = 0;

static int import_sample(void)
{
    _point_api = (_PointAPIMethods*) PyCapsule_Import("sample._point_api", 0);
    return (_point_api != NULL) ? 1 : 0;
}


#define PyPoint_AsPoint(obj) (_point_api->aspoint)(obj)
#define PyPoint_FromPoint(obj) (_point_api->frompoint)(obj)
#endif

#ifdef __cplusplus
}
#endif
