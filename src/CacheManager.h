//
//   File name      : CacheManager.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-22 15:39:11
//

#ifndef _CACHEMANAGER_H_
#define _CACHEMANAGER_H_

// Inherite header
// ...

// C system headers
// ...

// C++ system headers
#include <map>
#include <set>

// Headers from other projects
// ...

// Headers of current project
#include "IFDataType/Tstring.h"
#include "IFDataType/DataHolder.h"

//  This class manages a directory containing all cached files and a cache-list
//      file.

class DataHolder;
typedef std::string CACHE_KEY;
typedef std::string CACHE_VALUE;
typedef std::map<CACHE_KEY, CACHE_VALUE> CACHE_MAP;
typedef std::set<CACHE_VALUE> CACHE_VALUE_SET;

// First call set_cache_directory_path(...), and then use Instance().

class CacheManager
{
    static CacheManager *s_instance_;
    static Tstring s_cache_directory_path_;

    const Tstring kCacheDirectoryPath_;
    const Tstring kCacheListFilePath_;

    //  The key is the URL.
    //  The value is the relative path in the cache directory.
    CACHE_MAP cache_items_;

    // set of all cache values in c-string form.
    CACHE_VALUE_SET cache_value_set_;
public:
    static CacheManager& Instance();
    static void set_cache_directory_path(const Tstring &kCacheDirectoryPath);

    //  Searching for an cache item whose url is @kURL.
    //  If target item is found, return the cached data.
    //  Otherwise, throw an exception: NoSuchCacheException.
    DATAHOLDER_PTR Find(const std::string &kURL) const;

    //  Add a new cache item to the manage.
    //  This function will generate a local-file-path, save @kPageData there,
    //      and add the url-path-pair to the tail of match-list file.
    void Add(const std::string &kURL, const DataHolder &kPageData);

    //  Remove a cache item if it exists.
    //  Even if there's no cache for this kURL, this method will not throw any exception.
    void remove(const std::string &kURL);
protected:
private:
    CacheManager(const Tstring &kCacheDirectoryPath);
    ~CacheManager(){}

    //  Read the cache-list file in the directory specified by @cache_items_,
    //      and save the items into @cache_items_.
    //  If the file didn't exist, nothing would happen.
    void LoadCacheListFile();

    CACHE_VALUE GetUnusedCacheValue() const;

    //  Append a cache item (url, cache-file-path) to match-list, both in RAM
    //      and in hard disk.
    void AppendCacheItemToRAM(const std::string &kURL, const CACHE_VALUE &kValue);

    //  generate a new available cache-data-file path.
    //  Only relative path in the cache-directory.
    CACHE_VALUE GenerateCacheValue(time_t value_1, int value_2) const;

    //  "cache value" is the value in cache-index file.
    //  "file path" is a path for fopen(...) to read and write.
    Tstring TransformCacheValueToCacheFilePath(const CACHE_VALUE &kCacheValue) const;
};

#endif
