//
//   File name      : UrlDownloaderFactoryWithCache.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-30 15:44:26
//

// Implemented header
#include "UrlDownloaderFactoryWithCache.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "UrlDownloaderWithCache.h"

URLDOWNLOADER_PTR UrlDownloaderFactoryWithCache::Create()
{
    return URLDOWNLOADER_PTR(
        new UrlDownloaderWithCache(
            my_curl_easy_init_,
            my_curl_easy_setopt_,
            my_curl_easy_perform_,
            my_curl_easy_cleanup_,
            cache_manager_
        )
    );
}
