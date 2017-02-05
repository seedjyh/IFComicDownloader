//
//   File name      : CallLuaFunctionFailed.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-05 16:52:14
//

#ifndef _CALLLUAFUNCTIONFAILED_H_
#define _CALLLUAFUNCTIONFAILED_H_ 1

// Inherited header
#include "IFDataType/IFException.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

// C++调用某LUA脚本中的函数时出错，则C++抛出该异常。
class CallLuaFunctionFailed: public IFException
{
public:
    CallLuaFunctionFailed(const std::string &kFunctionName, const std::string &kReason)
    :   IFException(std::string("Failed in lua function ") + kFunctionName + " because " + kReason){}
    virtual ~CallLuaFunctionFailed(){}
protected:
private:
};

#endif
