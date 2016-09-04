//
//   File name      : TestPythonFunction.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-03 21:45:26
//

#ifdef _GTEST_

// Tested header
#include "PythonFunction.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <gtest/gtest.h>

// Headers of current project
// ...

TEST(PythonFunction, Add)
{
    ASSERT_EQ(3, PythonFunction::Add(1, 2));
    ASSERT_EQ(1, PythonFunction::Add(-1, 2));
    ASSERT_EQ(-3, PythonFunction::Add(-1, -2));
}

#endif
