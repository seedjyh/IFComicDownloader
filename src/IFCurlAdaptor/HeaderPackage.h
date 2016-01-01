//
//   File name      : HeaderPackage.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFComicDownloader.IFCurlAdaptor
//
//   Create datetime: 2011-03-15 14:31:35
//

#ifndef _IFCOMICDOWNLOADER_IFCURLADAPTOR_H_
#define _IFCOMICDOWNLOADER_IFCURLADAPTOR_H_ 1

// Tested or implemented header
// ...

// C system headers
#include <stddef.h>

// C++ system headers
#include <vector>
#include <string>
using namespace std;

// Headers from other projects
// ...

// Headers of current project
// ...

class HeaderPackage
{
    vector <string> header_list_;
public:
    HeaderPackage(){header_list_.clear();}
    ~HeaderPackage(){};

    // 如果收到过Content-Length并格式正确，则返回true
    // 否则返回false
    int GetContentLength(size_t &content_length) const;
    int GetContentEncoding(std::string &ret_encoding) const;
    int NeedRedirection() const;
    int GetRedirectionURL(std::string &ret_redirection_url) const;

    static size_t process_header(void *buffer, size_t size, size_t nmemb, void *user_p);

protected:
private:
    const static size_t s_kMemoryGridSize;
};

#endif
