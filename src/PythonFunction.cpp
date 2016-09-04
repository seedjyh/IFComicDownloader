//
//   File name      : PythonFunction.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-03 21:48:15
//

// Inherited header
#include "PythonFunction.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <Python.h>

// Headers of current project
// ...

int PythonFunction::Add(int a, int b)
{
    PyObject *main_module = PyImport_ImportModule("__main__");
    PyObject *main_dict = PyModule_GetDict(main_module);

    PyObject *a_obj = PyInt_FromLong(a);
    PyDict_SetItemString(main_dict, "a", a_obj);

    PyObject *b_obj = PyInt_FromLong(b);
    PyDict_SetItemString(main_dict, "b", b_obj);

    PyRun_SimpleString("sum = a + b");

    PyObject *sum_obj = PyMapping_GetItemString(main_dict, "sum");
    return PyInt_AsLong(sum_obj);
}
