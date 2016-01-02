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
// ...

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
    assert(NULL == s_instance_); // When the instance has been called, argument would become useless.
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

    boost::shared_ptr<FileHolder> file_data(DirectoryTreeLoader::ReadFile(TransformCacheValueToFilePath(ite->second)));
    return DATAHOLDER_PTR(new DataHolder(file_data->size(), file_data->content()));
}

void CacheManager::Add(const std::string &kURL, const DataHolder &kPageData)
{
    Tstring file_path_as_cache_value = GetUnusedCacheFilePath();
    FILE *fp = _tfopen((TransformCacheValueToFilePath(file_path_as_cache_value)).c_str(), _T("wb"));
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
    AppendCacheItemToList(kURL, file_path_as_cache_value);
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
    TCHAR t_cache_file_path[1024] = { '\0' };
    while (2 == fscanf(fp, "%s %S", url, t_cache_file_path))
    {
        cache_items_[std::string(url)] = Tstring(t_cache_file_path);
    }
    MY_FCLOSE(fp);
    return;
}

Tstring CacheManager::GetUnusedCacheFilePath() const
{
    Tstring file_path;
    time_t time_number = time(NULL);
    for (int i = 0;;i++)
    {
        file_path = GenerateCacheFilePath(time_number, i);
        if (!PathHandler::CheckFileExistance(file_path))
        {
            return file_path;
        }
    }
}

void CacheManager::AppendCacheItemToList(const std::string &kURL, const Tstring &kPath)
{
    FILE *fp = _tfopen(kCacheListFilePath_.c_str(), _T("ab"));
    if (NULL == fp)
    {
        throw - 1; // FileIOException?
    }
    int written_count = fprintf(fp, "%s %S\n", kURL.c_str(), kPath.c_str());
    if (written_count <= 0)
    {
        MY_FCLOSE(fp);
        throw -1; // FileIOException?
    }
    MY_FCLOSE(fp);
    cache_items_.insert(std::pair<std::string, Tstring>(kURL, kPath));
    return;
}

Tstring CacheManager::GenerateCacheFilePath(time_t value_1, int value_2) const
{
    TCHAR buffer[128] = {'\0' };
    int written_count = _stprintf(buffer, _T("%u_%d.cache"), static_cast<unsigned int>(value_1), value_2);
    if (written_count <= 0)
    {
        throw -1;
    }
    return Tstring(buffer);
}

Tstring CacheManager::TransformCacheValueToFilePath(const Tstring &kCacheValue) const
{
    return kCacheDirectoryPath_ + kCacheValue;
}
