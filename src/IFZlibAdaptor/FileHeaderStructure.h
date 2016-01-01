//
//   File name      : FileHeaderStructure.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFZlibAdaptor
//
//   Create datetime: 2013-01-08 11:14:49
//

#ifndef _IFZLIBADAPTOR_FILEHEADERSTRUCTURE_H_
#define _IFZLIBADAPTOR_FILEHEADERSTRUCTURE_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFDataType/Tstring.h"

// Headers of current project
// ...

class FileHeaderStructure
{
    unsigned int    sign_;
    unsigned short  uncompress_version_;
    unsigned short  general_mark_;
    unsigned short  compress_method_;
    unsigned short  last_modify_time_;
    unsigned short  last_modify_date_;
    unsigned int    crc_parity_code_32_;
    unsigned int    file_size_after_being_compressed_;
    unsigned int    original_file_size_;
    unsigned short  file_path_name_length_;
    unsigned short  expend_segment_length_;
    Tstring         file_related_path_name_;
    // expend segment
public:
    FileHeaderStructure();
    ~FileHeaderStructure(){};

    int ReadFromFile(FILE *fin);
protected:
private:
};

#endif

