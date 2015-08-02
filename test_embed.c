/*************************************************************************
	> File Name: test_embed.c
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2015年08月01日 星期六 20时02分22秒
    > Describition: 
 ************************************************************************/

#include <stdio.h>
#include "embed.h"

/* Load a symbol from a module */
PyObject* import_name(const char* modname, const char* symbol)
{
    PyObject* u_name;
    PyObject* module;
    u_name = PyUnicode_FromString(modname);
    module = PyImport_Import(u_name);
    Py_DECREF(u_name);
    return PyObject_GetAttrString(module, symbol);
}


int main()
{
    PyObject* pow_func;
    double x;

    Py_Initialize();
    pow_func = import_name("math", "pow");

    for (x = 0.0; x < 10.0; x += 1.0) {
        printf("%0.2f %0.2f\n", x, call_func(pow_func, x, 2.0));
    }

    Py_DECREF(pow_func);
    Py_Finalize();
    return 0;
}
