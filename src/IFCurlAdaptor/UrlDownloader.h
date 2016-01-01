//
//   File name      : UrlDownloader.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFCurlAdaptor
//
//   Create datetime: 2011-03-30 14:30:09
//

#ifndef _IFCURLADAPTOR_URLDOWNLOADERBASE_H_
#define _IFCURLADAPTOR_URLDOWNLOADERBASE_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <string>
#include <boost/shared_ptr.hpp>
using namespace std;

// Headers from other projects
#include "IFDataType/DataHolder.h"

// Headers of current project
#include "CurlFunctionPointers.h"

class ProxyArgument;
class CacheManager;

class UrlDownloader
{
    CurlEasyInit    my_curl_easy_init_;
    CurlEasySetOpt  my_curl_easy_setopt_;
    CurlEasyPerform my_curl_easy_perform_;
    CurlEasyCleanUp my_curl_easy_cleanup_;

    DataHolder buffer_;
    size_t page_total_len_; // 第一时间取得，用于下载进度的计算
public:
    UrlDownloader(
        CurlEasyInit    my_curl_easy_init,
        CurlEasySetOpt  my_curl_easy_setopt,
        CurlEasyPerform my_curl_easy_perform,
        CurlEasyCleanUp my_curl_easy_cleanup
    );
    virtual ~UrlDownloader(){}

    // 下载url所指向的文件，直到完全下载完成
    // 返回下载的数据包
    // 如果下载不可逆转地失败了，抛出带有失败原因的异常
    // @kURL不可空
    // @kRefererURL和@kCookie可空，表示没有。
    virtual DATAHOLDER_PTR Download(const string &kURL, const string &kRefererURL, const string &kCookie);

protected:
private:
};

typedef boost::shared_ptr<UrlDownloader> URLDOWNLOADER_PTR;

#endif
