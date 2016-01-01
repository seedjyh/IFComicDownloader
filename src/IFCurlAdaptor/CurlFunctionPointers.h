//
//   File name      : CurlFunctionPointers.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFCurlAdaptor
//
//   Create datetime: 2014-05-12 16:31:46
//

#ifndef _IFCURLADAPTOR_INCLUDE_CURLFUNCTIONPOINTERS_H_
#define _IFCURLADAPTOR_INCLUDE_CURLFUNCTIONPOINTERS_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <curl/curl.h>

// Headers of current project
// ...

typedef CURL* (*CurlEasyInit)(void);
typedef CURLcode (*CurlEasySetOpt)(CURL *curl, CURLoption option, ...);
typedef CURLcode (*CurlEasyPerform)(CURL *curl);
typedef void (*CurlEasyCleanUp)(CURL *curl);

#endif

