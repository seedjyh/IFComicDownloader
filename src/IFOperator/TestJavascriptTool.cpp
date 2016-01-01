//
//   File name      : TestJavascriptTool.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-01 17:29:39
//

#ifdef _GTEST_

// Tested or implemented header
#include "JavascriptTool.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <gtest/gtest.h>

// Headers of current project
// ...

TEST(JavascriptTool, Eval)
{
    const std::string kRawData(
        "eval(function(p,a,c,k,e,d){e=function(c){return(c<a?'':e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--)d[e(c)]=k[c]||e(c);k=[function(e){return d[e]}];e=function(){return'\\w+'};c=1};while(c--)if(k[c])p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c]);return p}('3/0.4,3/1.4,3/2.4',62,5,'1|2|3|a|jpg'.split('|'),0,{}))"
        );
    std::string result;
    ASSERT_NO_THROW(result = JavascriptTool::Eval(kRawData));
    ASSERT_STREQ("a/1.jpg,a/2.jpg,a/3.jpg", result.c_str());
}

TEST(JavascriptTool, ParseConfusionFunction)
{
    const std::string kRawData(
        "eval(function(p,a,c,k,e,d){e=function(c){return(c<a?'':e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--)d[e(c)]=k[c]||e(c);k=[function(e){return d[e]}];e=function(){return'\\w+'};c=1};while(c--)if(k[c])p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c]);return p}('4/0.6,4/1.6,4/2.6,5/3.6',62,7,'1|2|3|4|a|b|jpg'.split('|'),0,{}))"
        );
    std::string data;
    std::string type;
    std::string dictionary;
    ASSERT_NO_THROW(JavascriptTool::ParseConfusionFunction(kRawData, data, type, dictionary));
    ASSERT_STREQ("4/0.6,4/1.6,4/2.6,5/3.6", data.c_str());
    ASSERT_STREQ("62", type.c_str());
    ASSERT_STREQ("1|2|3|4|a|b|jpg", dictionary.c_str());
}

TEST(JavascriptTool, Deconfuse)
{
    const std::string kConfusedData("4/0.6,4/1.6,4/2.6,5/3.6");
    const std::string kConfusedType("62");
    const std::string kDictionary("1|2|3|4|a|b|jpg");
    std::string result;
    ASSERT_NO_THROW(result = JavascriptTool::Deconfuse(kConfusedData, kConfusedType, kDictionary));
    ASSERT_STREQ("a/1.jpg,a/2.jpg,a/3.jpg,b/4.jpg", result.c_str());
}

TEST(JavascriptTool, Deconfuse_WithBlank)
{
    const std::string kConfusedData("4/0.6,4/1.6,4/2.6,5/3.6");
    const std::string kConfusedType("62");
    const std::string kDictionary("1|2|3|4|a||jpg");
    std::string result;
    ASSERT_NO_THROW(result = JavascriptTool::Deconfuse(kConfusedData, kConfusedType, kDictionary));
    ASSERT_STREQ("a/1.jpg,a/2.jpg,a/3.jpg,5/4.jpg", result.c_str());
}

TEST(JavascriptTool, ParseDictionary)
{
    DictionaryMap result = JavascriptTool::ParseDictionary(std::string("a|b|jpg|d"));
    ASSERT_EQ(4, result.size());
    ASSERT_STREQ("a", result[0].c_str());
    ASSERT_STREQ("b", result[1].c_str());
    ASSERT_STREQ("jpg", result[2].c_str());
    ASSERT_STREQ("d", result[3].c_str());
}

TEST(JavascriptTool, TransferBase)
{
    ASSERT_EQ(0, JavascriptTool::TransferBase(std::string("0"), std::string("62")));
    ASSERT_EQ(1, JavascriptTool::TransferBase(std::string("1"), std::string("62")));
    ASSERT_EQ(9, JavascriptTool::TransferBase(std::string("9"), std::string("62")));
    ASSERT_EQ(10, JavascriptTool::TransferBase(std::string("a"), std::string("62")));
    ASSERT_EQ(35, JavascriptTool::TransferBase(std::string("z"), std::string("62")));
    ASSERT_EQ(36, JavascriptTool::TransferBase(std::string("A"), std::string("62")));
    ASSERT_EQ(61, JavascriptTool::TransferBase(std::string("Z"), std::string("62")));
    ASSERT_EQ(3843, JavascriptTool::TransferBase(std::string("ZZ"), std::string("62")));
}

#endif