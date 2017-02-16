//
//   File name      : FileOperator.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : RIG_VSBS
//
//   Create datetime: 2017-02-16 12:21:15
//

// Implemented header
#include "../include/FileOperator.h"

// C system headers
#ifdef WIN32
#include <windows.h>
#endif

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

bool FileOperator::rename(const std::string &kOldUri, const std::string &kNewUri)
{
    return (0 == ::rename(kOldUri.c_str(), kNewUri.c_str()));
}
