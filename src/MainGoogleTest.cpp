//
//   File name      : MainGoogleTest.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-21 10:20:28
//

#ifdef _GTEST_

// Implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <gtest/gtest.h>
#include <Python.h>

// Headers of current project
#include "PauseWhenDestruct.h"
#include "PythonInterface.h"

int main(int arg_count, char **arg_list)
{
    PauseWhenDestruct pauser;
    PythonInterface python_interface;
    Py_Initialize();
    testing::InitGoogleTest(&arg_count, arg_list);
    return RUN_ALL_TESTS();
}

#endif
