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
#include "IFMacros/BasicOperateMacro.h"

// Headers of current project
#include "LoadLibraryFailedException.h"
#include "UrlDownloaderSimple.h"

UrlDownloaderFactory::UrlDownloaderFactory(const Tstring &kDLLPath)
:   my_curl_easy_init_(NULL),
    my_curl_easy_setopt_(NULL),
    my_curl_easy_perform_(NULL),
    my_curl_easy_cleanup_(NULL)
{
    HINSTANCE Hint = LoadLibrary(kDLLPath.c_str());
    if (NULL == Hint)
    {
        TCHAR reason[1024];
        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            0,
            (LPTSTR)&reason,
            MY_SIZE_OF_ARRAY(reason),
            NULL);

        throw LoadLibraryFailedException(kDLLPath, CodeTransformer::TransTstringToString(Tstring(reason)));
    }

    my_curl_easy_init_ = (CurlEasyInit)GetProcAddress(Hint, "curl_easy_init");
    my_curl_easy_setopt_ = (CurlEasySetOpt)GetProcAddress(Hint, "curl_easy_setopt");
    my_curl_easy_perform_ = (CurlEasyPerform)GetProcAddress(Hint, "curl_easy_perform");
    my_curl_easy_cleanup_ = (CurlEasyCleanUp)GetProcAddress(Hint, "curl_easy_cleanup");
}

URLDOWNLOADER_PTR UrlDownloaderFactory::Create()
{
    return URLDOWNLOADER_PTR(
        new UrlDownloaderSimple(
            my_curl_easy_init_,
            my_curl_easy_setopt_,
            my_curl_easy_perform_,
            my_curl_easy_cleanup_
        )
    );
}
