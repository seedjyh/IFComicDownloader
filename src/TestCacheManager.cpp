//
//   File name      : TestCacheManager.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-23 15:41:08
//

#ifdef _GTEST_

// Implemented header
#include "CacheManager.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <gtest/gtest.h>

// Headers of current project
#include "IFOperator/PathHandler.h"
#include "IFOperator/DirectoryTreeLoader.h"
#include "exception/NoSuchCacheException.h"
#include "IFDataType/DataHolder.h"
#include "IFDataType/FileHolder.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFDataType/DirectoryHolder.h"

static bool SameContent(const FileHolder &kFile, const DataHolder &kData)
{
    if (kFile.size() != kData.size())
    {
        return false;
    }

    if (0 == kFile.size())
    {
        return true;
    }

    if (memcmp(kFile.content(), kData.content(), kFile.size() ) != 0)
    {
        return false;
    }

    return true;
}

static void WriteFile(const Tstring &kIndexFilePath, const DataHolder &kData)
{
    FILE *fp = _tfopen(kIndexFilePath.c_str(), _T("wb"));
    if (fwrite(kData.content(), 1, kData.size(), fp) != kData.size())
    {
        throw 1;
    }
    MY_FCLOSE(fp);
    return;
}

static void WriteCacheIndexFile(
    const Tstring &kIndexFilePath,
    const std::string &kURL,
    const Tstring &kCacheFilePath
)
{
    char buffer[1024] = { '\0' };
    if (0 >= sprintf(buffer, "%s %S\n", kURL.c_str(), kCacheFilePath.c_str()))
    {
        throw 1;
    }
    WriteFile(kIndexFilePath, DataHolder(std::string(buffer)));
    return;
}

TEST(CacheManager, LoadCacheIndexFile_Find_Add)
{
    const std::string kCachedURL_1("http://www.baidu.com/");
    const DataHolder kCachedData_1(std::string("<html>Hello, baidu!</html>"));
    const std::string kCachedURL_2("http://www.google.com/");
    const DataHolder kCachedData_2(std::string("<html>Gooooooooooogle!</html>"));

    const Tstring kTestDirectoryPath(_T("test\\"));
    const Tstring kCacheIndexFilePath = kTestDirectoryPath + _T("cache.index");
    const Tstring kCacheFilePath = _T("abc.html");

    // prepare directory and files.
    DirectoryHolder test_directory_holder(kTestDirectoryPath);
    WriteFile(kTestDirectoryPath + kCacheFilePath, kCachedData_1);
    WriteCacheIndexFile(kCacheIndexFilePath, kCachedURL_1, kCacheFilePath);

    // test
    CacheManager::set_cache_directory_path(kTestDirectoryPath);
    ASSERT_TRUE(kCachedData_1 == *(CacheManager::Instance().Find(kCachedURL_1)));

    // not found
    ASSERT_THROW(CacheManager::Instance().Find(kCachedURL_2), NoSuchCacheException);

    // add
    CacheManager::Instance().Add(kCachedURL_2, kCachedData_2);

    // found
    ASSERT_TRUE(kCachedData_2 == *(CacheManager::Instance().Find(kCachedURL_2)));
}

#endif
