//
//   File name      : UrlDownloaderSimple.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-04 19:34:09
//

#ifndef _URLDOWNLOADERSIMPLE_H_
#define _URLDOWNLOADERSIMPLE_H_ 1

// Inherited header
#include "UrlDownloader.h"

// C system headers
// ...

// C++ system headers
#include <string>
#include <boost/shared_ptr.hpp>

// Headers from other projects
#include "IFDataType/DataHolder.h"

// Headers of current project
#include "CurlFunctionPointers.h"

class UrlDownloaderSimple: public UrlDownloader
{
    CurlEasyInit    my_curl_easy_init_;
    CurlEasySetOpt  my_curl_easy_setopt_;
    CurlEasyPerform my_curl_easy_perform_;
    CurlEasyCleanUp my_curl_easy_cleanup_;

    DataHolder buffer_;
    size_t page_total_len_; // 第一时间取得，用于下载进度的计算
public:
    UrlDownloaderSimple(
        CurlEasyInit    my_curl_easy_init,
        CurlEasySetOpt  my_curl_easy_setopt,
        CurlEasyPerform my_curl_easy_perform,
        CurlEasyCleanUp my_curl_easy_cleanup
    );
    virtual ~UrlDownloaderSimple(){}

    // 下载url所指向的文件，直到完全下载完成
    // 返回下载的数据包
    // 如果下载不可逆转地失败了，抛出带有失败原因的异常
    // @kURL不可空
    // @kRefererURL和@kCookie可空，表示没有。
    virtual DATAHOLDER_PTR Download(const std::string &kURL, const std::string &kRefererURL, const std::string &kCookie);

protected:
private:
};

#endif
