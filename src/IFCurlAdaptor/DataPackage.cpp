//
//   File name      : DataPackage.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2011-03-15 10:03:21
//

// Tested or implemented header
#include "DataPackage.h"

// C system headers
#include <string.h>

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "IFMacros/BasicMacro.h"

const size_t DataPackage::s_kMemoryGridSize = 2048;

DataPackage::~DataPackage()
{
    MY_DELETEARRAY(buffer_);
};

size_t DataPackage::process_data(void *buffer, size_t size, size_t nmemb, void *user_p)
{
    DataPackage *data_package = (DataPackage *)user_p;
    size_t uWriteCount = size * nmemb;

    while (data_package->buffer_size_ < data_package->content_len_ + uWriteCount)
    {
        size_t new_size = 0;
        if (0 == data_package->buffer_size_)
        {
            data_package->buffer_size_ = s_kMemoryGridSize;
            data_package->buffer_ = new char[data_package->buffer_size_];
            if (!data_package->buffer_)
            {
                return 0;
            }
        }
        else
        {
            new_size = data_package->buffer_size_ * 2;
            char *new_buffer = new char[new_size];
            if (!new_buffer)
            {
                return 0;
            }

            memcpy(new_buffer, data_package->buffer_, data_package->content_len_);
            data_package->buffer_size_ = new_size;
            MY_DELETEARRAY(data_package->buffer_);
            data_package->buffer_ = new_buffer;
        }
    }

    memcpy(data_package->buffer_ + data_package->content_len_, buffer, uWriteCount);
    data_package->content_len_ += uWriteCount;

    return uWriteCount;
}