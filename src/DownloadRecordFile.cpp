//
//   File name      : DownloadRecordFile.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-01 15:13:27
//

// Inherited header
#include "DownloadRecordFile.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "IFMacros/BasicOperateMacro.h"

const Tstring DownloadRecordFile::s_kFileName_(__T("url.txt"));

DownloadRecordFile::DownloadRecordFile(const DownloadInfo &kDownloadInfo)
    : download_info_(kDownloadInfo){}

void DownloadRecordFile::Write(const Tstring &kComicPath) const
{
    Tstring file_full_path = kComicPath + s_kFileName_;
    FILE *fp = _tfopen(file_full_path.c_str(), __T("a"));
    if (NULL == fp)
    {
        printf("Error! Can not create/open comic download record file.\n");
        throw - 1;
    }
    fprintf(fp, "%s\n", download_info_.toLogLine().c_str());
    MY_FCLOSE(fp);

    return;
}

