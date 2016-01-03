//
//   File name      : AnalyseFailedException.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-29 09:05:49
//

#ifndef _URLANALYSEFAILEDEXCEPTION_H_
#define _URLANALYSEFAILEDEXCEPTION_H_ 1

// Inherite header
#include "IFDataType/IFException.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class UrlAnalyseFailedException: public IFException
{
public:
    UrlAnalyseFailedException(const std::string &kURL, const std::string &kReason)
    :   IFException(std::string("Analyse URL failed, url=") + kURL + ", reason=kReason"){}
    virtual ~UrlAnalyseFailedException(){}
protected:
private:
};

#endif
