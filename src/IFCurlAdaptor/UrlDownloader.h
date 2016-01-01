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
    size_t page_total_len_; // ��һʱ��ȡ�ã��������ؽ��ȵļ���
public:
    UrlDownloader(
        CurlEasyInit    my_curl_easy_init,
        CurlEasySetOpt  my_curl_easy_setopt,
        CurlEasyPerform my_curl_easy_perform,
        CurlEasyCleanUp my_curl_easy_cleanup
    );
    virtual ~UrlDownloader(){}

    // ����url��ָ����ļ���ֱ����ȫ�������
    // �������ص����ݰ�
    // ������ز�����ת��ʧ���ˣ��׳�����ʧ��ԭ����쳣
    // @kURL���ɿ�
    // @kRefererURL��@kCookie�ɿգ���ʾû�С�
    virtual DATAHOLDER_PTR Download(const string &kURL, const string &kRefererURL, const string &kCookie);

protected:
private:
};

typedef boost::shared_ptr<UrlDownloader> URLDOWNLOADER_PTR;

#endif
