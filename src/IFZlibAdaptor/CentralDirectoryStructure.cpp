//
//   File name      : CentralDirectoryStructure.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFZlibAdaptor
//
//   Create datetime: 2013-01-08 07:20:38
//

// Tested or implemented header
#include "CentralDirectoryStructure.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFMacros/BasicProcessMacro.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFOperator/CodeTransformer.h"

// Headers of current project
// ...

#define READ_VARIABLE_FROM_FILE(variable, file) fread(&variable, sizeof(variable), 1, file)

CentralDirectoryStructure::CentralDirectoryStructure()
:   sign_(0),
    os_(0),
    uncompress_version_(0),
    general_mark_(0),
    compress_method_(0),
    last_modify_time_(0),
    last_modify_date_(0),
    crc_parity_code_32_(0),
    file_size_after_being_compressed_(0),
    original_file_size_(0),
    file_path_name_length_(0),
    expend_segment_length_(0),
    disk_start_id_(0),
    inner_file_properties_(0),
    outer_file_properties_(0),
    file_header_block_offset_(0)
{
    file_related_path_name_.clear();
}

int CentralDirectoryStructure::ReadFromFile(FILE *fin)
{
    int nRetCode = false;
    int nResult  = false;

    char read_buffer[1024];

    nRetCode = READ_VARIABLE_FROM_FILE(sign_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(os_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(uncompress_version_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(general_mark_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(compress_method_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(last_modify_time_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(last_modify_date_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(crc_parity_code_32_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(file_size_after_being_compressed_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(original_file_size_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(file_path_name_length_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(expend_segment_length_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(file_comment_length_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(disk_start_id_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(inner_file_properties_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(outer_file_properties_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    nRetCode = READ_VARIABLE_FROM_FILE(file_header_block_offset_, fin);
    MY_PROCESS_ERROR(1 == nRetCode);

    MY_PROCESS_ERROR(file_path_name_length_ < MY_SIZE_OF_ARRAY(read_buffer) );

    memset(read_buffer, 0 , sizeof(read_buffer) );

    nRetCode = fread(read_buffer, 1, file_path_name_length_, fin);
    MY_PROCESS_ERROR(nRetCode == file_path_name_length_);

    nRetCode = CodeTransformer::TransStringToTString(std::string(read_buffer), file_related_path_name_);
    MY_PROCESS_ERROR(nRetCode);

    nRetCode = fseek(fin, ftell(fin) + expend_segment_length_ + file_comment_length_, SEEK_SET);
    MY_PROCESS_ERROR(0 == nRetCode);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}
