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
#include "exception/DownloadFailedException.h"
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
        CodeTransformer::TransStringToTString(GetFileNameExtentionFromFileURL(kFileURL));
    if (PathHandler::CheckFileExistance(kFilePath))
    {
        return;
    }

    while (1)
    {
        // download file
        UrlDownloaderFactory downloader_factory(ProgramArguments::Instance().curl_dll_path());
        URLDOWNLOADER_PTR downloader = downloader_factory.Create();
        try
        {
            DATAHOLDER_PTR data = downloader->Download(kFileURL, kURL, std::string(""));
            WriteFile(kFilePath.c_str(), data);
            break;
        }
        catch (DownloadFailedException &e)
        {
            printf("%s\n", e.message().c_str());
            printf("Download failed, retry... ");
        }
    }
    
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

std::string PictureDownloader::GetFileNameExtentionFromFileURL(const std::string &kURL)
{
    std::string result(strrchr(kURL.c_str(), '.'));

    // 有些URL后面还带上一个类似动态页面的参数，例如：http://manhua1025.61-174-50-141.cdndm5.com/20/19620/245859/1_9128.jpg?cid=245859&key=eca7f3ed56d8b4c2872ab88c33bddd81
    // 所以要去掉问号后面的部分。
    const char *kQuestionMark = strchr(result.c_str(), '?');
    if (kQuestionMark != NULL)
    {
        result.resize(kQuestionMark - result.c_str());
    }
    return result;
}
