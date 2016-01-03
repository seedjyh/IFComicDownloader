//
//   File name      : ComicDownloader.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-03 00:50:24
//

// Tested or implemented header
#include "ComicDownloader.h"

// C system headers
// ...

// C++ system headers
#include <iostream>

// Headers from other projects
#include "IFOperator/CodeTransformer.h"
#include "IFOperator/PathHandler.h"

// Headers of current project
#include "exception/UrlAnalyseFailedException.h"
#include "VolumeDownloader.h"

void ComicDownloader::Download(const std::string &kURL, const Tstring &kDownloadRootPath)
{
    std::cout << kURL << std::endl;
    const char *kResult = NULL;
    const char *kErrorMessage = NULL;
    if (!lua_state_->CallFunction("ComicUrlAnalyse", "s>s", kURL.c_str(), &kResult, &kErrorMessage))
    {
        throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
    }
    const std::string kAnalyseResult(kResult);

    if (!lua_state_->CallFunction("ComicPageGetComicTitle", "s>s", kAnalyseResult.c_str(), &kResult, &kErrorMessage))
    {
        throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
    }
    const std::string kComicTitle(kResult);

    const Tstring kComicPath = kDownloadRootPath + CodeTransformer::TransStringToTString(kComicTitle) + _T("\\");
    if (!PathHandler::CreatePath(kComicPath))
    {
        throw IFException(std::string("Creating comic path failed: comic title is ") + kComicTitle);
    }

    int volume_count = 0;
    if (!lua_state_->CallFunction("ComicPageGetVolumeCount", "s>i", kAnalyseResult.c_str(), &volume_count, &kErrorMessage))
    {
        throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
    }

    for (int i = 1; i <= volume_count; i++)
    {
        if (!lua_state_->CallFunction("ComicPageGetVolumeURL", "si>s", kAnalyseResult.c_str(), i, &kResult, &kErrorMessage))
        {
            throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
        }
        const std::string kVolumeURL(kResult);

        VolumeDownloader volume_downloader(lua_state_);
        volume_downloader.Download(std::string(kVolumeURL), kComicPath);
    }
    return;
}