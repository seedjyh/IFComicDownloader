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
// ...

// C system headers
// ...

// C++ system headers
#include <string>
#include <sstream>

// Headers from other projects
#include "IFDataType/IFException.h"

// Headers of current project
// ...

class LoadLibraryFailedException: public IFException
{
    std::string lib_file_uri_;
    int error_code_;
public:
    LoadLibraryFailedException(const std::string &kLibFileURI, int error_code)
    :   lib_file_uri_(kLibFileURI),
        error_code_(error_code){};
    ~LoadLibraryFailedException(){};

    virtual void CreateMessage(std::string &ret_result) const
    {
        std::stringstream ss;
        ss << "load lib file " << lib_file_uri_ << " failed! Error code: " << error_code_;
        ret_result = ss.str();

        return;
    }

protected:
private:
    const char* GetName() const {return "LoadLibraryFailedException";}
};

#endif
