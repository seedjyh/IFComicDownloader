//
//   File name      : UrlDownloaderFactoryImpl.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFCurlAdaptor
//
//   Create datetime: 2011-03-30 14:48:22
//

// Tested or implemented header
#include "UrlDownloaderFactoryImpl.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFOperator/CodeTransformer.h"

// Headers of current project
#include "UrlDownloaderImpl.h"
#include "UrlDownloaderImplWithProxy.h"
#include "ProxyArgument.h"
#include "LoadLibraryFailedException.h"

UrlDownloaderFactoryImpl::UrlDownloaderFactoryImpl(const Tstring &kDLLPath)
:   proxy_argument_(NULL),
    my_curl_easy_init_(NULL),
    my_curl_easy_setopt_(NULL),
    my_curl_easy_perform_(NULL),
    my_curl_easy_cleanup_(NULL)
{
    HINSTANCE Hint = LoadLibrary(kDLLPath.c_str() );
    if (NULL == Hint)
    {
        DWORD error_code = GetLastError();
        std::string temp_dll_uri;
        CodeTransformer::TransTstringToString(kDLLPath, temp_dll_uri);
        throw LoadLibraryFailedException(temp_dll_uri, error_code);
    }

    my_curl_easy_init_    = (CurlEasyInit)GetProcAddress(Hint,"curl_easy_init");
    my_curl_easy_setopt_  = (CurlEasySetOpt)GetProcAddress(Hint,"curl_easy_setopt");
    my_curl_easy_perform_ = (CurlEasyPerform)GetProcAddress(Hint,"curl_easy_perform");
    my_curl_easy_cleanup_ = (CurlEasyCleanUp)GetProcAddress(Hint,"curl_easy_cleanup");
}

UrlDownloaderFactoryImpl::~UrlDownloaderFactoryImpl()
{
    MY_DELETE(proxy_argument_);
}

void UrlDownloaderFactoryImpl::SetProxyOn(const ProxyArgument &kProxyArgument)
{
    LockerCtrl locker_ctrl(locker_);
    SetProxyOff();
    proxy_argument_ = new ProxyArgument(kProxyArgument);
    return;
}

void UrlDownloaderFactoryImpl::SetProxyOff()
{
    LockerCtrl locker_ctrl(locker_);
    MY_DELETE(proxy_argument_);
    return;
}

UrlDownloader* UrlDownloaderFactoryImpl::Create(const string &kURL, const string &kRefererURL, const string &kCookie)
{
    LockerCtrl locker_ctrl(locker_);
    UrlDownloader *result = NULL;

    string formated_url("");
    string formated_ref_url("");

    CodeTransformer::FormatUrltoUtf8(kURL, formated_url);
    CodeTransformer::FormatUrltoUtf8(kRefererURL, formated_ref_url);

    if (proxy_argument_)
    {
        result = new UrlDownloaderImplWithProxy(
            formated_url, formated_ref_url, kCookie, *proxy_argument_,
            my_curl_easy_init_,
            my_curl_easy_setopt_,
            my_curl_easy_perform_,
            my_curl_easy_cleanup_
        );
    }
    else
    {
        result = new UrlDownloaderImpl(
            formated_url, formated_ref_url, kCookie,
            my_curl_easy_init_,
            my_curl_easy_setopt_,
            my_curl_easy_perform_,
            my_curl_easy_cleanup_
        );
    }
    return result;
}
