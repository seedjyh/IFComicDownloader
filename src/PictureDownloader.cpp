//
//   File name      : PictureDownloader.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-03 07:27:32
//

// Tested or implemented header
#include "PictureDownloader.h"

// C system headers
// ...

// C++ system headers
#include <iostream>

// Headers from other projects
#include "IFOperator/NumberOperator.h"
#include "IFDataType/Tstring.h"
#include "IFOperator/CodeTransformer.h"
#include "IFCurlAdaptor/UrlDownloaderFactory.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFOperator/PathHandler.h"

// Headers of current project
#include "exception/UrlAnalyseFailedException.h"
#include "ProgramArguments.h"

void PictureDownloader::Download(const std::string &kURL, const Tstring &kDownloadRootPath)
{
    // getting file URL
    const char *kResult = NULL;
    const char *kErrorMessage = NULL;
    if (!lua_state_->CallFunction("PictureUrlAnalyse", "s>s", kURL.c_str(), &kResult, &kErrorMessage))
    {
         throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
    }
    const std::string kAnalyseResult(kResult);

    if (!lua_state_->CallFunction("FindFileUrl", "s>s", kAnalyseResult.c_str(), &kResult, &kErrorMessage))
    {
        throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
    }
    const std::string kFileURL(kResult);

    // getting file index (from 1)
    int file_index = 0;
    if (!lua_state_->CallFunction("GetPageIndexFromURL", "s>i", kURL.c_str(), &file_index, &kErrorMessage))
    {
        throw UrlAnalyseFailedException(kURL, std::string((kErrorMessage != NULL) ? kErrorMessage : ""));
    }

    // generate file path
    const Tstring kFilePath =
        kDownloadRootPath +
        PathHandler::ValidateName(CodeTransformer::TransStringToTString(comic_title_ + "_" + volume_title_ + "_")) +
        NumberOperator::ItoA(file_index, Tstring(_T("%06u"))) +
        CodeTransformer::TransStringToTString(std::string(strrchr(kFileURL.c_str(), '.')));
    if (PathHandler::CheckFileExistance(kFilePath))
    {
        return;
    }

    // download file
    UrlDownloaderFactory downloader_factory(ProgramArguments::Instance().curl_dll_path());
    URLDOWNLOADER_PTR downloader = downloader_factory.Create();
    DATAHOLDER_PTR data = downloader->Download(kFileURL, kURL, std::string(""));

    // write data to hard disk
    WriteFile(kFilePath.c_str(), data);
    
    return;
}

void PictureDownloader::WriteFile(const Tstring &kPath, DATAHOLDER_PTR data)
{
    FILE *fp = _tfopen(kPath.c_str(), _T("wb"));
    if (fwrite(data->content(), 1, data->size(), fp) != data->size())
    {
        throw 1;
    }
    MY_FCLOSE(fp);
    return;
}