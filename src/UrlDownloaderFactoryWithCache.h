//
//   File name      : UrlDownloaderFactoryWithCache.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-30 14:55:09
//

#ifndef _URLDOWNLOADERFACTORYWITHCACHE_H_
#define _URLDOWNLOADERFACTORYWITHCACHE_H_ 1

// Inherite header
#include "IFCurlAdaptor/UrlDownloaderFactory.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class CacheManager;

class UrlDownloaderFactoryWithCache : public UrlDownloaderFactory
{
    CacheManager &cache_manager_;
public:
    UrlDownloaderFactoryWithCache(const Tstring &kDLLPath, CacheManager &cache_manager)
    :   UrlDownloaderFactory(kDLLPath),
        cache_manager_(cache_manager){}
    virtual ~UrlDownloaderFactoryWithCache(){}

    virtual URLDOWNLOADER_PTR Create();
protected:
private:
};

#endif
