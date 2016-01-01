//
//   File name      : JavascriptTool.h
//
//   Code by        : Yonghang Jiang
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-01 17:14:33
//

#ifndef _JAVASCRIPTTOOL_H_
#define _JAVASCRIPTTOOL_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <string>
#include <map>

// Headers from other projects
// ...

// Headers of current project
// ...

typedef std::map<int, std::string> DictionaryMap;

class JavascriptTool
{
public: // as interface
    static std::string Eval(const std::string &kSrc);
public: // inner methods for test
    static void ParseConfusionFunction(const std::string &kSrc, std::string &ret_confused_data, std::string &ret_confuse_base, std::string &ret_dictionary);
    static std::string Deconfuse(const std::string &kConfusedData, const std::string &kConfuseBase, const std::string &kDictionaryText);
    static DictionaryMap ParseDictionary(const std::string &kDictionaryText);
    static int TransferBase(const std::string &kSrc, const std::string &kBase);
protected:
private:
    JavascriptTool(){}
    ~JavascriptTool(){}
};

#endif
