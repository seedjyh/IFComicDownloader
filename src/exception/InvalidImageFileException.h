//
//   File name      : InvalidImageFileException.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-16 23:51:55
//

#ifndef _INVALIDIMAGEFILEEXCEPTION_H_
#define _INVALIDIMAGEFILEEXCEPTION_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "IFDataType/IFException.h"

class InvalidImageFileException : public IFException
{
public:
    InvalidImageFileException(const std::string &kFileURL, const std::string &kPictureURL)
    :   IFException(std::string("Invalid image file (FileURL=") + kFileURL + ", PictureURL=" + kPictureURL + ")"){}
    virtual ~InvalidImageFileException(){}
protected:
private:
};


#endif
