//
//   File name      : UrlDownloaderFactory.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFCurlAdaptor
//
//   Create datetime: 2011-03-30 14:48:22
//

// Tested or implemented header
#include "UrlDownloaderFactory.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFOperator/CodeTransformer.h"

// Headers of current project
#include "LoadLibraryFailedException.h"

UrlDownloaderFactory::UrlDownloaderFactory(const Tstring &kDLLPath)
:   my_curl_easy_init_(NULL),
    my_curl_easy_setopt_(NULL),
    my_curl_easy_perform_(NULL),
    my_curl_easy_cleanup_(NULL)
{
    HINSTANCE Hint = LoadLibrary(kDLLPath.c_str());
    if (NULL == Hint)
    {
        DWORD error_code = GetLastError();
        std::string temp_dll_uri;
        CodeTransformer::TransTstringToString(kDLLPath, temp_dll_uri);
        throw LoadLibraryFailedException(temp_dll_uri, error_code);
    }

    my_curl_easy_init_ = (CurlEasyInit)GetProcAddress(Hint, "curl_easy_init");
    my_curl_easy_setopt_ = (CurlEasySetOpt)GetProcAddress(Hint, "curl_easy_setopt");
    my_curl_easy_perform_ = (CurlEasyPerform)GetProcAddress(Hint, "curl_easy_perform");
    my_curl_easy_cleanup_ = (CurlEasyCleanUp)GetProcAddress(Hint, "curl_easy_cleanup");
}

URLDOWNLOADER_PTR UrlDownloaderFactory::Create()
{
    return URLDOWNLOADER_PTR(
        new UrlDownloader(
            my_curl_easy_init_,
            my_curl_easy_setopt_,
            my_curl_easy_perform_,
            my_curl_easy_cleanup_
        )
    );
}
