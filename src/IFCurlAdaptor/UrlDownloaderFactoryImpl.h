//
//   File name      : UrlDownloaderFactoryImpl.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFCurlAdaptor
//
//   Create datetime: 2011-03-30 14:51:07
//

#ifndef _IFCURLADAPTOR_URLDOWNLOADERFACTORYIMPL_H_
#define _IFCURLADAPTOR_URLDOWNLOADERFACTORYIMPL_H_ 1

// Tested or implemented header
#include "UrlDownloaderFactory.h"

// C system headers
// ...

// C++ system headers
#include <string>
using namespace std;

// Headers from other projects
#include "IFDataType/Locker.h"
#include "IFDataType/Tstring.h"

// Headers of current project
#include "CurlFunctionPointers.h"

class ProxyArgument;

class UrlDownloaderFactoryImpl: public UrlDownloaderFactory
{
    Locker locker_;
    ProxyArgument *proxy_argument_;

    CurlEasyInit    my_curl_easy_init_;
    CurlEasySetOpt  my_curl_easy_setopt_; 
    CurlEasyPerform my_curl_easy_perform_;
    CurlEasyCleanUp my_curl_easy_cleanup_;

public:
    UrlDownloaderFactoryImpl(const Tstring &kDLLPath);
    virtual ~UrlDownloaderFactoryImpl();

    void SetProxyOn(const ProxyArgument &kProxyArgument);
    void SetProxyOff();

    virtual UrlDownloader* Create(const string &kURL, const string &kRefererURL, const string &kCookie);
protected:
private:
};

#endif
