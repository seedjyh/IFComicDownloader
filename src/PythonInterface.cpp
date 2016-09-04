//
//   File name      : PythonInterface.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-04 05:46:59
//

// Inherited header
#include "PythonInterface.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <Python.h>

// Headers of current project
// ...

PythonInterface::PythonInterface()
{
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        throw - 1;
    }
}

PythonInterface::~PythonInterface()
{
    Py_Finalize();
}
