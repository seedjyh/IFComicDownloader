//
//   File name      : DownloadRecordFile.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-01 15:09:53
//

#ifndef _DOWNLOADRECORDFILE_H_
#define _DOWNLOADRECORDFILE_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "IFDataType/Tstring.h"
#include "DownloadInfo.h"

// This class is responsible to record the time and URL of comic
// to a text file in the directory where this comic book saved.

class DownloadRecordFile
{
    static const Tstring s_kFileName_;

    DownloadInfo download_info_;
public:
    DownloadRecordFile(const DownloadInfo &kDownloadInfo);
    ~DownloadRecordFile(){}

    void Write(const Tstring &kComicPath) const;
protected:
private:
};

#endif
