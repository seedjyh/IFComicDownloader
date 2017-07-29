//
//   File name      : UrlDownloaderSimple.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-30 10:49:21
//

// Implemented header
#include "UrlDownloaderSimple.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFOperator/CodeTransformer.h"
#include "exception/DownloadFailedException.h"

// Headers of current project
#include "DataPackage.h"
#include "HeaderPackage.h"

static const string s_kUserAgent("Mozilla/5.0 (Windows NT 5.1) LIBCURL/7.19.7.0");
static size_t s_kDownloadWaitSecond = 600;

UrlDownloaderSimple::UrlDownloaderSimple(
    CurlEasyInit    my_curl_easy_init,
    CurlEasySetOpt  my_curl_easy_setopt,
    CurlEasyPerform my_curl_easy_perform,
    CurlEasyCleanUp my_curl_easy_cleanup
) : my_curl_easy_init_(my_curl_easy_init),
    my_curl_easy_setopt_(my_curl_easy_setopt),
    my_curl_easy_perform_(my_curl_easy_perform),
    my_curl_easy_cleanup_(my_curl_easy_cleanup),
    page_total_len_(0){}

DATAHOLDER_PTR UrlDownloaderSimple::Download(const string &kURL, const string &kRefererURL, const string &kCookie)
{
    DataPackage data_package;
    HeaderPackage header_package;

    std::string formated_url = CodeTransformer::FormatUtf8StrToUrl(kURL);
    string formated_ref_url  = CodeTransformer::FormatUtf8StrToUrl(kRefererURL);

    CURL *curl = my_curl_easy_init_();
    if (NULL == curl)
    {
        throw DownloadFailedException(kURL, std::string("my_curl_easy_init_ returned NULL"));
    }

    my_curl_easy_setopt_(curl, CURLOPT_URL, formated_url.c_str());
    my_curl_easy_setopt_(curl, CURLOPT_WRITEFUNCTION, &DataPackage::process_data);
    my_curl_easy_setopt_(curl, CURLOPT_WRITEDATA, &data_package);
    my_curl_easy_setopt_(curl, CURLOPT_HEADERFUNCTION, &HeaderPackage::process_header);
    my_curl_easy_setopt_(curl, CURLOPT_HEADERDATA, &header_package);
    my_curl_easy_setopt_(curl, CURLOPT_TIMEOUT, s_kDownloadWaitSecond);
    my_curl_easy_setopt_(curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate, sdch");
    my_curl_easy_setopt_(curl, CURLOPT_SSL_VERIFYPEER, false);
    if (formated_ref_url.size() > 0)
    {
        my_curl_easy_setopt_(curl, CURLOPT_REFERER, formated_ref_url.c_str());
    }

    my_curl_easy_setopt_(curl, CURLOPT_USERAGENT, s_kUserAgent.c_str());

    if (kCookie.size() > 0)
    {
        my_curl_easy_setopt_(curl, CURLOPT_COOKIE, kCookie.c_str());
    }

    CURLcode ret_code = my_curl_easy_perform_(curl);
    if (ret_code != CURLE_OK)
    {
        printf("Error: my_curl_easy_perform_ returns %d.\n", ret_code);
        throw DownloadFailedException(kURL, std::string("my_curl_easy_perform_ returned something else but not CURLE_OK"));
    }

    my_curl_easy_cleanup_(curl);
    curl = NULL;
    return DATAHOLDER_PTR(new DataHolder(data_package.content_len(), data_package.buffer()));
}
