//
//   File name      : UrlDownloaderFactory.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFCurlAdaptor
//
//   Create datetime: 2011-03-30 14:51:07
//

#ifndef _IFCURLADAPTOR_URLDOWNLOADERFACTORY_H_
#define _IFCURLADAPTOR_URLDOWNLOADERFACTORY_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <string>
using namespace std;

// Headers from other projects
#include "IFDataType/Tstring.h"

// Headers of current project
#include "CurlFunctionPointers.h"
#include "UrlDownloader.h"

class CacheManager;

class UrlDownloaderFactory
{
public:
    UrlDownloaderFactory(const Tstring &kDLLPath);
    virtual ~UrlDownloaderFactory(){}

    virtual URLDOWNLOADER_PTR Create();
protected:
    CurlEasyInit    my_curl_easy_init_;
    CurlEasySetOpt  my_curl_easy_setopt_;
    CurlEasyPerform my_curl_easy_perform_;
    CurlEasyCleanUp my_curl_easy_cleanup_;
private:
};

#endif
