//
//   File name      : UrlDownloader.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-30 10:49:21
//

// Implemented header
#include "UrlDownloader.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFOperator/CodeTransformer.h"

// Headers of current project
#include "DataPackage.h"
#include "HeaderPackage.h"

static const string s_kUserAgent("Mozilla/5.0 (Windows NT 5.1) LIBCURL/7.19.7.0");
static size_t s_kDownloadWaitSecond = 60;

UrlDownloader::UrlDownloader(
    CurlEasyInit    my_curl_easy_init,
    CurlEasySetOpt  my_curl_easy_setopt,
    CurlEasyPerform my_curl_easy_perform,
    CurlEasyCleanUp my_curl_easy_cleanup
) : my_curl_easy_init_(my_curl_easy_init),
    my_curl_easy_setopt_(my_curl_easy_setopt),
    my_curl_easy_perform_(my_curl_easy_perform),
    my_curl_easy_cleanup_(my_curl_easy_cleanup),
    page_total_len_(0){}

DATAHOLDER_PTR UrlDownloader::Download(const string &kURL, const string &kRefererURL, const string &kCookie)
{
    DataPackage data_package;
    HeaderPackage header_package;

    string formated_url("");
    string formated_ref_url("");

    CodeTransformer::FormatUrltoUtf8(kURL, formated_url);
    CodeTransformer::FormatUrltoUtf8(kRefererURL, formated_ref_url);

    CURL *curl = my_curl_easy_init_();
    if (NULL == curl)
    {
        throw 1;
    }

    my_curl_easy_setopt_(curl, CURLOPT_URL, kURL.c_str());
    my_curl_easy_setopt_(curl, CURLOPT_WRITEFUNCTION, &DataPackage::process_data);
    my_curl_easy_setopt_(curl, CURLOPT_WRITEDATA, &data_package);
    my_curl_easy_setopt_(curl, CURLOPT_HEADERFUNCTION, &HeaderPackage::process_header);
    my_curl_easy_setopt_(curl, CURLOPT_HEADERDATA, &header_package);
    my_curl_easy_setopt_(curl, CURLOPT_TIMEOUT, s_kDownloadWaitSecond);
    if (kRefererURL.size() > 0)
    {
        my_curl_easy_setopt_(curl, CURLOPT_REFERER, kRefererURL.c_str());
    }

    my_curl_easy_setopt_(curl, CURLOPT_USERAGENT, s_kUserAgent.c_str());

    if (kCookie.size() > 0)
    {
        my_curl_easy_setopt_(curl, CURLOPT_COOKIE, kCookie.c_str());
    }

    if (my_curl_easy_perform_(curl) != CURLE_OK)
    {
        throw 1;
    }

    my_curl_easy_cleanup_(curl);
    curl = NULL;
    return DATAHOLDER_PTR(new DataHolder(data_package.content_len(), data_package.buffer()));
}
