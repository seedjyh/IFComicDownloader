//
//   File name      : UnsupportedSiteException.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-02 16:20:23
//

#ifndef _UNSUPPORTEDSITEEXCEPTION_H_
#define _UNSUPPORTEDSITEEXCEPTION_H_ 1

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

class UnsupportedSiteException: public IFException
{
public:
    UnsupportedSiteException(const std::string &kURL)
    :   IFException(std::string("URL ") + kURL + " is not supported yet"){}
protected:
private:
};

#endif
