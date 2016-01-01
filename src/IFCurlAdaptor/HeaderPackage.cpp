//
//   File name      : HeaderPackage.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFComicDownloader.IFCurlAdaptor
//
//   Create datetime: 2011-03-15 14:36:37
//

// Tested or implemented header
#include "HeaderPackage.h"

// C system headers
#include <string.h>
#pragma warning(disable:4996)

// C++ system headers
#include <sstream>

// Headers from other projects
#include "IFMacros/BasicMacro.h"

// Headers of current project
// ...


// HTTP/1.1 200 OK
// 

int HeaderPackage::GetContentLength(size_t &content_length) const
{
    int nResult  = false;
    int nRetCode = false;

    int content_length_header_exists = false;
    int read_result = 0;

    for (size_t i = 0; i < header_list_.size(); i++)
    {
        if (!strnicmp(header_list_[i].c_str(), "Content-Length", strlen("Content-Length") ) )
        {
            content_length_header_exists = true;

            nRetCode = sscanf(strchr(header_list_[i].c_str() + strlen("Content-Length"), ':') + 1, "%d", &read_result);
            MY_PROCESS_ERROR(nRetCode > 0);

            break;
        }
    }

    MY_PROCESS_ERROR(content_length_header_exists);

// Exit1:
    content_length = read_result;
    nResult = true;
Exit0:
    return nResult;
}


int HeaderPackage::GetContentEncoding(std::string &ret_encoding) const
{
    int nResult  = false;
    int nRetCode = false;

    int target_header_exists = false;
    int read_result = 0;
    static const std::string target_header_name("Content-Encoding");

    for (size_t i = 0; i < header_list_.size(); i++)
    {
        if (!strnicmp(header_list_[i].c_str(), target_header_name.c_str(), target_header_name.length() ) )
        {
            target_header_exists = true;

            stringstream ss;
            ss << strchr(header_list_[i].c_str() + target_header_name.length(), ':') + 1;
            ss >> ret_encoding;

            break;
        }
    }

    MY_PROCESS_ERROR(target_header_exists);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int HeaderPackage::NeedRedirection() const
{
    static const std::string target_header_name("Location");
    for (int i = 0; i < (int)header_list_.size(); i++)
    {
        if (!strnicmp(header_list_[i].c_str(), target_header_name.c_str(), target_header_name.length() ) )
        {
            return true;
        }
    }
    return false;
}

int HeaderPackage::GetRedirectionURL(std::string &ret_redirection_url) const
{
    int nResult  = false;
    int nRetCode = false;

    int target_header_exists = false;
    int read_result = 0;
    static const std::string target_header_name("Location");

    for (size_t i = 0; i < header_list_.size(); i++)
    {
        if (!strnicmp(header_list_[i].c_str(), target_header_name.c_str(), target_header_name.length() ) )
        {
            target_header_exists = true;

            stringstream ss;
            ss << strchr(header_list_[i].c_str() + target_header_name.length(), ':') + 1;
            ss >> ret_redirection_url;

            break;
        }
    }

    MY_PROCESS_ERROR(target_header_exists);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}


size_t HeaderPackage::process_header(void *buffer, size_t size, size_t nmemb, void *user_p)
{
    HeaderPackage *data_package = (HeaderPackage *)user_p;
    size_t uWriteCount = size * nmemb;
    const char* char_buffer = reinterpret_cast<const char*>(buffer);

    if (!char_buffer)
    {
        return 0;
    }

    //if (
    //    ('\r' == char_buffer[0]) &&
    //    ('\n' == char_buffer[1])
    //)
    //{
    //    return 0;
    //}

    data_package->header_list_.push_back(string((char*)buffer, 0, uWriteCount) );

    return uWriteCount;
}
