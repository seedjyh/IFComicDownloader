//
//   File name      : TestLuaStateImpl.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2012-04-08 23:15:8
//

#ifdef _GTEST_

// Tested or implemented header
#include "IFLuaHandler/LuaStateImpl.h"

// C system headers
#include <windows.h>

// C++ system headers
// ...

// Headers from other projects
#include <gtest/gtest.h>
#include "IFDataType/PathTypes.h"
#include "IFMacros/BasicOperateMacro.h"
#include "lua.hpp"

// Headers of current project
// ...


#define FILE_1 ".\\file_1.lua"
#define FILE_2 ".\\file_2.lua"
#define FILE_3 ".\\file_3.lua"
#define FILE_4 ".\\file_4.lua"

static void CreateFiles()
{
    FILE *fp = NULL;
    
    fp = fopen(FILE_1, "wb");
    assert(fp != NULL);
    fputs("function add(x, y) return x + y end\n", fp);
    fputs("function minus(x, y) return x - y end\n", fp);
    fclose(fp);

    fp = fopen(FILE_2, "wb");
    assert(fp != NULL);
    fputs("function time(x, y) return x * y end\n", fp);
    fputs("function divide(x, y) return x / y end\n", fp);
    fclose(fp);

    fp = fopen(FILE_3, "wb");
    assert(fp != NULL);
    fputs("function stringcat(x, y) return x .. y end\n", fp);
    fclose(fp);

    fp = fopen(FILE_4, "wb");
    assert(fp != NULL);
    fputs("site_mode=\".kyo.cn\"\n\nfunction SiteCheck(x)\n	local _, result_end_index=string.find(x, site_mode, 1)\n    if type(result_end_index) ~= \"number\" then\n        return 0\n    end\n    return 1\nend\n", fp);
    fclose(fp);

    return;
}

static void RemoveFiles()
{
    DeleteFile(TEXT(FILE_1) );
    DeleteFile(TEXT(FILE_2) );
    DeleteFile(TEXT(FILE_3));
    DeleteFile(TEXT(FILE_4));
    return;
}

TEST(LuaStateImpl, LoadFiles_CallFunction)
{
    CreateFiles();

    LuaStateImpl state;

    ASSERT_TRUE(state.LoadFile(Tstring(TEXT(FILE_1) ) ) );
    ASSERT_TRUE(state.LoadFile(Tstring(TEXT(FILE_2) ) ) );
    ASSERT_TRUE(state.LoadFile(Tstring(TEXT(FILE_3) ) ) );

    RemoveFiles();

    int    result_integer = 0;
    double result_double  = 0.0;
    const char *kResultString = NULL;

    ASSERT_TRUE(state.CallFunction("add", "ii>i", 3, 5, &result_integer) );
    ASSERT_EQ(8, result_integer);

    ASSERT_TRUE(state.CallFunction("add", "dd>d", 3.0, 5.0, &result_double) );
    ASSERT_TRUE(fabs(result_double - 8.0) < 0.00001);

    ASSERT_TRUE(state.CallFunction("minus", "ii>i", 3, 5, &result_integer) );
    ASSERT_EQ(-2, result_integer);

    ASSERT_TRUE(state.CallFunction("minus", "dd>d", 3.0, 5.0, &result_double) );
    ASSERT_TRUE(fabs(result_double - (-2.0) ) < 0.00001);

    ASSERT_TRUE(state.CallFunction("time", "ii>i", 3, 5, &result_integer) );
    ASSERT_EQ(15, result_integer);

    ASSERT_TRUE(state.CallFunction("time", "dd>d", 3.0, 5.0, &result_double) );
    ASSERT_TRUE(fabs(result_double - 15.0) < 0.00001);

    ASSERT_TRUE(state.CallFunction("divide", "ii>i", 3, 5, &result_integer) );
    ASSERT_EQ(0, result_integer);

    ASSERT_TRUE(state.CallFunction("divide", "dd>d", 3.0, 5.0, &result_double) );
    ASSERT_TRUE(fabs(result_double - 0.6) < 0.00001);

    ASSERT_TRUE(state.CallFunction("stringcat", "ss>s", "hello, ", "world", &kResultString) );
    ASSERT_STREQ("hello, world", kResultString);

    RemoveFiles();
}

TEST(LuaStateImpl, LoadFiles_CallFunction_SiteCheck)
{
    CreateFiles();

    LuaStateImpl state;

    ASSERT_TRUE(state.LoadFile(Tstring(TEXT(FILE_4) ) ) );

    RemoveFiles();

    int result = -1;
    ASSERT_TRUE(state.CallFunction("SiteCheck", "s>i", "http://www.kyo.cn/manhua/kexuedechaodiancipao.html", &result) );
    ASSERT_EQ(1, result);
    RemoveFiles();
}

TEST(LuaStateImpl, LoadBuffer)
{
	LuaStateImpl state;

	int result = 0;

	ASSERT_TRUE(state.LoadBuffer("function Add(a, b) return a + b + append_int end") );
	ASSERT_TRUE(state.LoadBuffer("append_int = 1000") );
	ASSERT_TRUE(state.CallFunction("Add", "ii>i", 3, 5, &result) );
	ASSERT_EQ(1008, result);
}

TEST(LuaStateImpl, LoadBuffer_MultiLines)
{
    LuaStateImpl state;

    int result = 0;

    ASSERT_TRUE(state.LoadBuffer("function Add(a, b) return a + b + append_int end\nappend_int = 1000\nfunction Minus(a, b) return a - b end\n") );
    ASSERT_TRUE(state.CallFunction("Add", "ii>i", 3, 5, &result) );
    ASSERT_EQ(1008, result);
    ASSERT_TRUE(state.CallFunction("Minus", "ii>i", 3, 5, &result) );
    ASSERT_EQ(-2, result);
}

#endif
