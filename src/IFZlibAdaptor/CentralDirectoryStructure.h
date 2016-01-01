//
//   File name      : CentralDirectoryStructure.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFZlibAdaptor
//
//   Create datetime: 2013-01-08 06:51:01
//

#ifndef _IFZLIBADAPTOR_CENTRALDIRECTORYSTRUCTURE_H_
#define _IFZLIBADAPTOR_CENTRALDIRECTORYSTRUCTURE_H_ 1

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

class CentralDirectoryStructure
{
    unsigned int    sign_;
    unsigned short  os_;
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
    unsigned short  file_comment_length_;
    unsigned short  disk_start_id_;
    unsigned short  inner_file_properties_;
    unsigned int    outer_file_properties_;
    unsigned int    file_header_block_offset_;
    Tstring         file_related_path_name_;
    // expend segment
    // file comment
public:
    CentralDirectoryStructure();
    ~CentralDirectoryStructure(){};

    int ReadFromFile(FILE *fin);

    int IsCompressed() const
    {
        return compress_method_ != 0;
    }

    unsigned int file_size_after_being_compressed() const
    {
        return file_size_after_being_compressed_;
    }

    int IsDirectory() const
    {
        return (outer_file_properties_ & 0x10) > 0;
    }

    unsigned int file_header_block_offset() const
    {
        return file_header_block_offset_;
    }

    const Tstring& file_related_path_name() const
    {
        return file_related_path_name_;
    }

protected:
private:
};

#endif
