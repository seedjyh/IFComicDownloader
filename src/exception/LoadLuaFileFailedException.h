//
//   File name      : LoadLuaFileFailedException.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-03 07:09:20
//

#ifndef _LOADLUAFILEFAILEDEXCEPTION_H_
#define _LOADLUAFILEFAILEDEXCEPTION_H_ 1

// Tested or implemented header
#include "IFDataType/IFException.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFDataType/Tstring.h"
#include "IFOperator/CodeTransformer.h"

// Headers of current project
// ...

class LoadLuaFileFailedException: public IFException
{
public:
    LoadLuaFileFailedException(const Tstring &kFilePath)
    :   IFException(std::string("Failed in loading lua file: ") + CodeTransformer::TransTstringToString(kFilePath)){}
    virtual ~LoadLuaFileFailedException(){}
protected:
private:
};

#endif
