//
//   File name      : DownloadInfo.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-01 15:22:30
//

#ifndef _DOWNLOADINFO_H_
#define _DOWNLOADINFO_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
#include <string>

// Headers from other projects
// ...

// Headers of current project
// ...

class DownloadInfo
{
    std::string comic_title_;
    std::string comic_url_;
public:
    DownloadInfo(const std::string &kComicTitle, const std::string &kComicURL)
    :   comic_title_(kComicTitle),
        comic_url_(kComicURL){}

    ~DownloadInfo(){}

    const std::string toLogLine() const;
protected:
private:
};

#endif
