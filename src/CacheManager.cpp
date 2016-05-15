//
//   File name      : CacheManager.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-23 16:01:39
//

// Implemented header
#include "CacheManager.h"

// C system headers
#include <time.h>

// C++ system headers
#include <sstream>

// Headers from other projects
#include "exception/NoSuchCacheException.h"
#include "IFDataType/DataHolder.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFOperator/PathHandler.h"
#include "IFOperator/CodeTransformer.h"
#include "IFDataType/FileHolder.h"
#include "IFOperator/DirectoryTreeLoader.h"

// Headers of current project
// ...

CacheManager* CacheManager::s_instance_ = NULL;
Tstring CacheManager::s_cache_directory_path_;

CacheManager& CacheManager::Instance()
{
    if (NULL == s_instance_)
    {
        s_instance_ = new CacheManager(s_cache_directory_path_);
    }
    return *s_instance_;
}

void CacheManager::set_cache_directory_path(const Tstring &kCacheDirectoryPath)
{
    MY_DELETE(s_instance_);
    s_cache_directory_path_ = kCacheDirectoryPath;
    return;
}

DATAHOLDER_PTR CacheManager::Find(const std::string &kURL) const
{
    CACHE_MAP::const_iterator ite = cache_items_.find(kURL);
    if (ite == cache_items_.end())
    {
        throw NoSuchCacheException(kURL);
    }

    CACHE_VALUE cache_value = ite->second;
    Tstring  cache_file_path = TransformCacheValueToCacheFilePath(cache_value);
    boost::shared_ptr<FileHolder> file_data(DirectoryTreeLoader::ReadFile(cache_file_path));
    return DATAHOLDER_PTR(new DataHolder(file_data->size(), file_data->content()));
}

void CacheManager::Add(const std::string &kURL, const DataHolder &kPageData)
{
    CACHE_VALUE new_cache_value = GetUnusedCacheValue();
    FILE *fp = _tfopen((TransformCacheValueToCacheFilePath(new_cache_value)).c_str(), _T("wb"));
    if (NULL == fp)
    {
        throw - 1;
    }
    size_t written_count = fwrite(kPageData.content(), 1, kPageData.size(), fp);
    if (written_count != kPageData.size())
    {
        throw -1;
    }
    MY_FCLOSE(fp);
    AppendCacheItemToRAM(kURL, new_cache_value);
    return;
}

CacheManager::CacheManager(const Tstring &kCacheDirectoryPath)
:   kCacheDirectoryPath_(kCacheDirectoryPath),
    kCacheListFilePath_(kCacheDirectoryPath + _T("cache.index"))
{
    if (!PathHandler::CreatePath(kCacheDirectoryPath_))
    {
        throw 1;
    }
    LoadCacheListFile();
}

void CacheManager::LoadCacheListFile()
{
    FILE *fp = _tfopen(kCacheListFilePath_.c_str(), _T("rb"));
    if (NULL == fp)
    {
        return; // No cache list file means there's no any cache items yet.
    }
    char url[1024] = { '\0' };
    char cache_value[1024] = { '\0' };
    while (2 == fscanf(fp, "%s %s", url, cache_value))
    {
        cache_items_[CACHE_KEY(url)] = CACHE_VALUE(cache_value);
        cache_value_set_.insert(std::string(cache_value));
    }
    MY_FCLOSE(fp);
    return;
}

CACHE_VALUE CacheManager::GetUnusedCacheValue() const
{
    time_t time_number = time(NULL);
    for (int i = 0;;i++)
    {
        CACHE_VALUE new_value = GenerateCacheValue(time_number, i);
        if (cache_value_set_.end() == cache_value_set_.find(new_value) )
        {
            return new_value;
        }
    }
}

void CacheManager::AppendCacheItemToRAM(const std::string &kURL, const CACHE_VALUE &kValue)
{
    FILE *fp = _tfopen(kCacheListFilePath_.c_str(), _T("ab"));
    if (NULL == fp)
    {
        throw - 1; // FileIOException?
    }
    int written_count = fprintf(fp, "%s %s\n", kURL.c_str(), kValue.c_str());
    if (written_count <= 0)
    {
        MY_FCLOSE(fp);
        throw -1; // FileIOException?
    }
    MY_FCLOSE(fp);
    cache_items_.insert(std::pair<CACHE_KEY, CACHE_VALUE>(kURL, kValue));
    cache_value_set_.insert(kValue);
    return;
}

CACHE_VALUE CacheManager::GenerateCacheValue(time_t value_1, int value_2) const
{
    std::stringstream ss;
    ss << value_1 << "_" << value_2 << ".cache";
    return ss.str();
}

Tstring CacheManager::TransformCacheValueToCacheFilePath(const CACHE_VALUE &kCacheValue) const
{
    return kCacheDirectoryPath_ + CodeTransformer::TransStringToTString(kCacheValue);
}
