//
//   File name      : LoadLibraryFailedException.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFCurlAdapter
//
//   Create datetime: 2014-05-13 09:03:01
//

#ifndef _IFCURLADAPTER_SRC_LOADLIBRARYFAILEDEXCEPTION_H_
#define _IFCURLADAPTER_SRC_LOADLIBRARYFAILEDEXCEPTION_H_ 1

// Tested or implemented header
#include "IFDataType/IFException.h"

// C system headers
// ...

// C++ system headers
#include <string>
#include <sstream>

// Headers from other projects
#include "IFDataType/Tstring.h"

// Headers of current project
#include "IFOperator/CodeTransformer.h"

class LoadLibraryFailedException: public IFException
{
    Tstring lib_file_uri_;
    int error_code_;
public:
    LoadLibraryFailedException(const Tstring &kLibFileURI, const std::string &kReason)
    :   IFException(std::string("load libary ") + CodeTransformer::TransTstringToString(kLibFileURI) + " failed because " + kReason){}
    ~LoadLibraryFailedException(){};
protected:
private:
};

#endif
