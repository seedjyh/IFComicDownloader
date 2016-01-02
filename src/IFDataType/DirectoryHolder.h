//
//   File name      : DirectoryHolder.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-02 15:25:29
//

#ifndef _DIRECTORYHOLDER_H_
#define _DIRECTORYHOLDER_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFOperator/PathHandler.h"

// Headers of current project
#include "Tstring.h"

class DirectoryHolder
{
    Tstring kPath_;
public:
    DirectoryHolder(const Tstring &kPath)
    :   kPath_(kPath)
    {
        if (!PathHandler::CreatePathRecursive(kPath_))
        {
            throw - 1;
        }
    }
    ~DirectoryHolder()
    {
        PathHandler::Remove(kPath_);
    }
protected:
private:
};

#endif
