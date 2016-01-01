//
//   File name      : IFCurlNeedRedirectionException.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFCurlAdaptor
//
//   Create datetime: 2012-10-05 12:45:19
//

#ifndef _IFCURLADAPTOR_INCLUDE_IFCURLNEEDREDIRECTIONEXCEPTION_H_
#define _IFCURLADAPTOR_INCLUDE_IFCURLNEEDREDIRECTIONEXCEPTION_H_ 1

// Tested or implemented header
#include "IFDataType/IFException.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class IFCurlNeedRedirectionException: public IFException
{
    std::string target_url_;
public:
    IFCurlNeedRedirectionException(const std::string &kTargetURL):  target_url_(kTargetURL){};
    virtual ~IFCurlNeedRedirectionException(){};

    const std::string& target_url() const {return target_url_;}
protected:
private:
    virtual const char* GetName() const {return "IFCurlNeedRedirectionException";}
};

#endif
