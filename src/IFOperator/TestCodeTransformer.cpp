//
//   File name      : TestCodeTransformer.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-03 09:20:56
//

#ifdef _GTEST_

// Tested or implemented header
#include "CodeTransformer.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <gtest/gtest.h>
#include "IFMacros/BasicOperateMacro.h"

// Headers of current project
// ...

TEST(CodeTransformer, TransCharToTchar)
{
    setlocale(LC_ALL, "chs");
    char c_str[] = { 0xbb, 0xb6, 0xd3, 0xad, 0xbc, 0xd3, 0xc8, 0xeb, 0x4e, 0x48, 0x4b };
    TCHAR t_str[1024];
    ASSERT_TRUE(CodeTransformer::TransCharToTchar(strlen(c_str), c_str, MY_SIZE_OF_ARRAY(t_str), t_str));
    ASSERT_EQ(0x6B22, t_str[0]);
}

#endif