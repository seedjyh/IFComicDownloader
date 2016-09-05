//
//   File name      : UrlDownloaderWithCache.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-30 15:50:48
//

// Implemented header
#include "UrlDownloaderWithCache.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "CacheManager.h"
#include "exception/NoSuchCacheException.h"

UrlDownloaderWithCache::UrlDownloaderWithCache(
    CurlEasyInit    my_curl_easy_init,
    CurlEasySetOpt  my_curl_easy_setopt,
    CurlEasyPerform my_curl_easy_perform,
    CurlEasyCleanUp my_curl_easy_cleanup,
    CacheManager &cache_manager
) : UrlDownloaderSimple(
        my_curl_easy_init,
        my_curl_easy_setopt,
        my_curl_easy_perform,
        my_curl_easy_cleanup
    ),
    cache_manager_(cache_manager){}

DATAHOLDER_PTR UrlDownloaderWithCache::Download(const std::string &kURL, const std::string &kRefererURL, const std::string &kCookie)
{
    try
    {
        return cache_manager_.Find(kURL);
    }
    catch (NoSuchCacheException &)
    {
        DATAHOLDER_PTR result = UrlDownloaderSimple::Download(kURL, kRefererURL, kCookie);
        cache_manager_.Add(kURL, *result);
        return result;
    }
}
