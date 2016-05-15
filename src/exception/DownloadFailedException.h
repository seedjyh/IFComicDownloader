//
//   File name      : DownloadFailedException.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-04-06 22:04:09
//

#ifndef _DOWNLOADFAILEDEXCEPTION_H_
#define _DOWNLOADFAILEDEXCEPTION_H_ 1

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

class DownloadFailedException : public IFException
{
public:
    DownloadFailedException(const std::string &kURL, const std::string &kReason)
    :   IFException(std::string("Failed in downloading url = ") + kURL + " because " + kReason){}
    virtual ~DownloadFailedException(){}
protected:
private:
};

#endif
