//
//   File name      : VolumeDownloader.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-03 06:51:15
//

// Tested or implemented header
#include "VolumeDownloader.h"

// C system headers
// ...

// C++ system headers
#include <iostream>

// Headers from other projects
#include "IFDataType/Tstring.h"
#include "IFOperator/CodeTransformer.h"
#include "IFOperator/PathHandler.h"

// Headers of current project
#include "exception/UrlAnalyseFailedException.h"
#include "PictureDownloader.h"

void VolumeDownloader::Download(const std::string &kURL, const Tstring &kDownloadRootPath)
{
    std::cout << "\t" << kURL << std::endl;
    const char *kResult = NULL;
    const char *kErrorMessage = NULL;
    if (!lua_state_->CallFunction("VolumeUrlAnalyse", "s>s", kURL.c_str(), &kResult, &kErrorMessage))
    {
        throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
    }
    const std::string kAnalyseResult(kResult);

    if (!lua_state_->CallFunction("VolumePageGetVolumeTitle", "s>s", kAnalyseResult.c_str(), &kResult, &kErrorMessage))
    {
        throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
    }
    const std::string kVolumeTitle(kResult);

    const Tstring kVolumePath = kDownloadRootPath + CodeTransformer::TransStringToTString(std::string(kVolumeTitle)) + _T("\\");
    if (!PathHandler::CreatePath(kVolumePath))
    {
        throw IFException(std::string("Creating volume path failed: volume title is ") + kVolumeTitle);
    }

    int picture_count = 0;
    if (!lua_state_->CallFunction("VolumePageGetPictureCount", "s>i", kAnalyseResult.c_str(), &picture_count, &kErrorMessage))
    {
        throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
    }

    for (int i = 1; i <= picture_count; i++)
    {
        if (!lua_state_->CallFunction("VolumePageGetPictureURL", "si>s", kAnalyseResult.c_str(), i, &kResult, &kErrorMessage))
        {
            throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
        }
        const std::string kVolumeURL(kResult);

        PictureDownloader picture_downloader(lua_state_);
        picture_downloader.Download(kVolumeURL, kVolumePath);
    }
    return;
}
