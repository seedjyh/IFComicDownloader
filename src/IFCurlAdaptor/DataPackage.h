//
//   File name      : DataPackage.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2011-03-15 10:01:15
//

#ifndef _IFCOMICDOWNLOADER_IFCURLADAPTOR_DATAPACKAGE_H_
#define _IFCOMICDOWNLOADER_IFCURLADAPTOR_DATAPACKAGE_H_ 1

// Tested or implemented header
// ...

// C system headers
#include <stddef.h>

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class DataPackage
{
    char   *buffer_;
    size_t  content_len_;
    size_t  buffer_size_;
public:
    DataPackage():buffer_(NULL),content_len_(0),buffer_size_(0){};
    ~DataPackage();

    const char* buffer() const {return buffer_;}
    size_t      content_len() const {return content_len_;}

    static size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p);

protected:
private:
    const static size_t s_kMemoryGridSize;
};



#endif
