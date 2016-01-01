//
//   File name      : IFException.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2012-06-05 13:27:40
//

#ifndef _IFDATATYPE_SRC_IFEXCEPTION_H_
#define _IFDATATYPE_SRC_IFEXCEPTION_H_ 1

// Tested or implemented header
#include "IFThrowable.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class IFException: public IFThrowable
{
    std::string message_;
public:
    IFException(){}
    IFException(const std::string &kMessage)
    :   message_(kMessage){}
    virtual ~IFException(){}

    const std::string& message() const { return message_; }
protected:
private:
};

#endif

