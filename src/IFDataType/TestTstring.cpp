//
//   File name      : TestTstring.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2011-03-23 14:32:15
//

#ifdef _GTEST_

// Tested or implemented header
#include "Tstring.h"

// C system headers
#include <tchar.h>
#include <string.h>
#include <windows.h>

// C++ system headers
// ...

// Headers from other projects
#include "gtest/gtest.h"

// Headers of current project
// ...

TEST(Tstring, Tstring_Default)
{
    Tstring str;

    ASSERT_EQ(0, str.size() );
    ASSERT_EQ(str.size(), str.length() );
}

TEST(Tstring, Tstring_TCHARArray)
{
    const TCHAR kValue[] = TEXT("hello, 你好， world 世界");
    Tstring str(kValue);

    ASSERT_EQ(_tcslen(kValue), str.size() );
    ASSERT_EQ(str.size(), str.length() );
    ASSERT_EQ(0, _tcscmp(kValue, str.c_str() ) );
}

TEST(Tstring, Tstring_Copy)
{
    Tstring old_str(TEXT("Give 给 me 我 power! 力量") );
    Tstring new_str(old_str);

    ASSERT_EQ(old_str.size(), new_str.size() );
    ASSERT_EQ(old_str.length(), new_str.length() );
    ASSERT_EQ(0, _tcscmp(old_str.c_str(), new_str.c_str() ) );
}

TEST(Tstring, resize)
{
    const TCHAR kValue[] = TEXT("Destiny 命运 A 人工 I 智能");
    Tstring str(kValue);

    ASSERT_EQ(_tcslen(kValue), str.size() );
    ASSERT_EQ(str.size(), str.length() );
    ASSERT_EQ(0, _tcscmp(kValue, str.c_str() ) );
}

TEST(Tstring, clear)
{
    Tstring str(TEXT("Destiny 命运 A 人工 I 智能") );

    str.clear();
    ASSERT_EQ(0, str.size() );
    ASSERT_EQ(str.size(), str.length() );
}

TEST(Tstring, assign)
{
    TCHAR *tstr = TEXT("Destiny 命运 A 人工 I 智能");
    Tstring str;
    ASSERT_EQ(0, str.length() );
    str.assign(tstr);

    ASSERT_EQ(0, _tcscmp(tstr, str.c_str() ) );
}

TEST(Tstring, operator_Equal)
{
    TCHAR *str = TEXT("Destiny 命运 A 人工 I 智能");
    Tstring a(str);
    Tstring b(str);
    ASSERT_TRUE(a == a);
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == a);

    Tstring c;
    ASSERT_FALSE(a == c);
}

TEST(Tstring, operator_Assign)
{
    Tstring old_str(TEXT("Give 给 me 我 power! 力量") );
    Tstring new_str;

    ASSERT_EQ(0, new_str.size() );
    ASSERT_EQ(0, new_str.length() );

    new_str = old_str;

    ASSERT_EQ(old_str.size(), new_str.size() );
    ASSERT_EQ(new_str.size(), new_str.length() );
    ASSERT_EQ(0, _tcscmp(old_str.c_str(), new_str.c_str() ) );
}

TEST(Tstring, operator_AppendOneTCHAR)
{
    Tstring old_str(TEXT("Give 给 me 我 power! 力量") );
    Tstring new_str;
    TCHAR append = TCHAR('~');

    new_str = old_str;

    new_str += append;
    ASSERT_EQ(old_str.size() + 1, new_str.size() );
    ASSERT_EQ(new_str.size(), new_str.length() );
    ASSERT_EQ(0, _tcsncmp(old_str.c_str(), new_str.c_str(), old_str.size() ) );
    ASSERT_EQ(append, new_str[new_str.size() - 1]);
}

TEST(Tstring, operator_AppendOneTCHAR_2)
{
    Tstring old_str(TEXT("Give 给 me 我 power! 力量") );
    Tstring new_str;
    TCHAR append = TEXT('！');

    new_str = old_str;

    new_str += append;
    ASSERT_EQ(old_str.size() + 1, new_str.size() );
    ASSERT_EQ(new_str.size(), new_str.length() );
    ASSERT_EQ(0, _tcsncmp(old_str.c_str(), new_str.c_str(), old_str.size() ) );
    ASSERT_EQ(append, new_str[new_str.size() - 1]);
}

TEST(Tstring, operator_AppendTCHARArray)
{
    Tstring old_str(TEXT("Give 给 me 我 power! 力量") );
    Tstring new_str;
    const TCHAR kAppend[] = TEXT("~……！！");

    new_str = old_str;

    new_str += kAppend;
    ASSERT_EQ(old_str.size() + _tcslen(kAppend), new_str.size() );
    ASSERT_EQ(new_str.size(), new_str.length() );
    ASSERT_EQ(0, _tcsncmp(old_str.c_str(), new_str.c_str(), old_str.size() ) );
    ASSERT_EQ(0, _tcscmp(kAppend, new_str.c_str() + old_str.size() ) );
}

TEST(Tstring, operator_AppendTstring)
{
    Tstring old_str(TEXT("Give 给 me 我 power! 力量") );
    Tstring new_str;
    Tstring append(TEXT("~……！！") );

    new_str = old_str;
    new_str += append;

    ASSERT_EQ(old_str.size() + append.size(), new_str.size() );
    ASSERT_EQ(new_str.size(), new_str.length() );
    ASSERT_EQ(0, _tcsncmp(old_str.c_str(), new_str.c_str(), old_str.size() ) );
    ASSERT_EQ(0, _tcscmp(append.c_str(), new_str.c_str() + old_str.size() ) );
}

TEST(Tstring, operator_Index)
{
    Tstring str(TEXT("阿兰·M·图灵") );

    ASSERT_EQ(TEXT('阿'), str[0]);
    ASSERT_EQ(TEXT('兰'), str[1]);
    ASSERT_EQ(TEXT('·'), str[2]);
    ASSERT_EQ(TEXT('M'), str[3]);
    ASSERT_EQ(TEXT('·'), str[4]);
    ASSERT_EQ(TEXT('图'), str[5]);
    ASSERT_EQ(TEXT('灵'), str[6]);
}

TEST(Tstring, operator_Index_const)
{
    const Tstring kStr(TEXT("阿兰·M·图灵") );

    ASSERT_EQ(TEXT('阿'), kStr[0]);
    ASSERT_EQ(TEXT('兰'), kStr[1]);
    ASSERT_EQ(TEXT('·'), kStr[2]);
    ASSERT_EQ(TEXT('M'),  kStr[3]);
    ASSERT_EQ(TEXT('·'), kStr[4]);
    ASSERT_EQ(TEXT('图'), kStr[5]);
    ASSERT_EQ(TEXT('灵'), kStr[6]);
}

TEST(Tstring, operator_TstringAddTCHARArray)
{
    const Tstring kStr(TEXT("红se") );
    const TCHAR kAppend[] = TEXT("的dong西");

    Tstring result = kStr + kAppend;
    ASSERT_EQ(kStr.size() + _tcslen(kAppend), result.size() );
    ASSERT_EQ(result.size(), result.length() );
    ASSERT_EQ(0, _tcscmp(TEXT("红se的dong西"), result.c_str() ) );
}

TEST(Tstring, operator_TCHARArrayAddTstring)
{
    const TCHAR kStr[] = TEXT("红se");
    const Tstring kAppend(TEXT("的dong西") );

    Tstring result = kStr + kAppend;
    ASSERT_EQ(_tcslen(kStr) + kAppend.size(), result.size() );
    ASSERT_EQ(result.size(), result.length() );
    ASSERT_EQ(0, _tcscmp(TEXT("红se的dong西"), result.c_str() ) );
}

TEST(Tstring, operator_TstringAddTstring)
{
    const Tstring kStr(TEXT("红se") );
    const Tstring kAppend(TEXT("的dong西") );

    Tstring result = kStr + kAppend;
    ASSERT_EQ(kStr.size() + kAppend.size(), result.size() );
    ASSERT_EQ(result.size(), result.length() );
    ASSERT_EQ(0, _tcscmp(TEXT("红se的dong西"), result.c_str() ) );
}

#endif
