//
//   File name      : NoSuchCacheException.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-23 15:56:51
//

#ifndef _NOSUCHCACHEEXCEPTION_H_
#define _NOSUCHCACHEEXCEPTION_H_ 1

// Inherite header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "IFDataType/IFException.h"

class NoSuchCacheException: public IFException
{
public:
    NoSuchCacheException(const std::string &kCacheKey)
    :   IFException(std::string("No such cache with key: ") + kCacheKey){}
    virtual ~NoSuchCacheException(){}
protected:
private:
};

#endif
