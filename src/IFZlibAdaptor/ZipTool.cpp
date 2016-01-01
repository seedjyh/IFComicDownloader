//
//   File name      : ZipTool.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFZlibAdaptor
//
//   Create datetime: 2013-01-05 21:26:37
//

// Tested or implemented header
#include "ZipTool.h"

// C system headers
#include <windows.h>
#include <tchar.h>
#include <assert.h>

// C++ system headers
// ...

// Headers from other projects
#include "IFDataType/Tstring.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFMacros/BasicProcessMacro.h"
#include "IFOperator/PathHandler.h"
#include "zlib.h"

// Headers of current project
#include "CentralDirectoryStructure.h"
#include "FileHeaderStructure.h"

#pragma pack(2)
typedef struct
{
    unsigned int    sign;
    unsigned short  disc_id;
    unsigned short  disc_central_content_begin_id;
    unsigned short  disc_central_content_entrance_count;
    unsigned short  file_count;
    unsigned int    central_content_length;
    unsigned int    central_content_offset;
    unsigned short  zip_file_comment_length;
}CentralContentEnding;

int ZipTool::Unzip(const Tstring &kZipFilePathName, const Tstring &kUnzipTargetPath)
{
    int nRetCode = false;
    int nResult  = false;

    CentralContentEnding ending_block;
    int current_offset = 0;

    memset(&ending_block, 0, sizeof(ending_block) );

    FILE *fin = _tfopen(kZipFilePathName.c_str(), TEXT("rb") );
    MY_PROCESS_ERROR(fin != NULL);

    nRetCode = fseek(fin, -static_cast<int>(sizeof(ending_block) ), SEEK_END);
    MY_PROCESS_ERROR(0 == nRetCode);

    nRetCode = fread(&ending_block, 1, sizeof(ending_block), fin);
    MY_PROCESS_ERROR(nRetCode > 0);

    assert(ending_block.sign == 0x06054B50);

    nRetCode = fseek(fin, ending_block.central_content_offset, SEEK_SET);
    MY_PROCESS_ERROR(0 == nRetCode);

    while (static_cast<int>(ending_block.central_content_offset + ending_block.central_content_length) > ftell(fin) )
    {
        CentralDirectoryStructure central_content_block;
        Tstring target_path_filename;

        nRetCode = central_content_block.ReadFromFile(fin);
        MY_PROCESS_ERROR(nRetCode);

        current_offset = ftell(fin);

        target_path_filename = kUnzipTargetPath + central_content_block.file_related_path_name();

        PathHandler::TransSlashToBackslash(target_path_filename);
        PathHandler::Validate(target_path_filename);

        nRetCode = fseek(fin, central_content_block.file_header_block_offset(), SEEK_SET);
        MY_PROCESS_ERROR(0 == nRetCode);

        if (central_content_block.IsDirectory() )
        {
            nRetCode = PathHandler::CreatePathRecursive(target_path_filename);
            MY_PROCESS_ERROR(nRetCode);
        }
        else
        {
            FILE *new_file = NULL;

            nRetCode = JumpFileHeader(fin);
            MY_PROCESS_ERROR(nRetCode);
            
            new_file = _tfopen(target_path_filename.c_str(), TEXT("wb") );
            MY_PROCESS_ERROR(new_file != NULL);

            if (central_content_block.IsCompressed() )
            {
                nRetCode = UnzipF2F(fin, central_content_block.file_size_after_being_compressed(), new_file);
                MY_PROCESS_ERROR(nRetCode);
            }
            else
            {
                nRetCode = CopyF2F(fin, central_content_block.file_size_after_being_compressed(), new_file);
                MY_PROCESS_ERROR(nRetCode);
            }

            MY_FCLOSE(new_file);
        }

        nRetCode = fseek(fin, current_offset, SEEK_SET);
        MY_PROCESS_ERROR(0 == nRetCode);
    }

// Exit1:
    nResult = true;
Exit0:
    MY_FCLOSE(fin);
    return nResult;
}

int ZipTool::UnzipF2F(FILE *fin, int all_in_length, FILE *fout)
{
    int nResult  = false;
    int nRetCode = false;

    Byte in_buffer[1024];
    Byte out_buffer[32768];
    int read_count = 0;
    int write_count = 0;

    z_stream_s unzip_stream;
    unzip_stream.next_in  = in_buffer;
    unzip_stream.avail_in = 0;
    unzip_stream.next_out  = out_buffer;
    unzip_stream.avail_out = MY_SIZE_OF_ARRAY(out_buffer);
    unzip_stream.zalloc   = Z_NULL;
    unzip_stream.zfree    = Z_NULL;
    unzip_stream.opaque   = Z_NULL;

    nRetCode = inflateInit2(&unzip_stream, -15);
    MY_PROCESS_ERROR(Z_OK == nRetCode);

    while (read_count < all_in_length)
    {
        int will_read_length = all_in_length - read_count;

        unzip_stream.next_in  = in_buffer;
        unzip_stream.avail_in = 0;
        unzip_stream.next_out  = out_buffer;
        unzip_stream.avail_out = MY_SIZE_OF_ARRAY(out_buffer);

        int zip_buffer_space_length = MY_SIZE_OF_ARRAY(in_buffer) - unzip_stream.avail_in;
        if (will_read_length > zip_buffer_space_length)
        {
            will_read_length = zip_buffer_space_length;
        }

        int actual_read_count = fread(in_buffer + unzip_stream.avail_in, 1, will_read_length, fin);
        MY_PROCESS_ERROR(actual_read_count == will_read_length);

        unzip_stream.avail_in += actual_read_count;

        read_count += actual_read_count;

        nRetCode = inflate(&unzip_stream, Z_NO_FLUSH);
        if (
            (nRetCode != Z_OK) &&
            (nRetCode != Z_STREAM_END)
        )
        {
            MY_PROCESS_ERROR(nRetCode);
        }

        nRetCode = fwrite(out_buffer, 1, unzip_stream.total_out - write_count, fout);
        MY_PROCESS_ERROR(nRetCode >= static_cast<int>(unzip_stream.total_out) - write_count);

        write_count = unzip_stream.total_out;
    }

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int ZipTool::JumpFileHeader(FILE *fin)
{
    int nResult  = false;
    int nRetCode = false;

    FileHeaderStructure file_header;

    nRetCode = file_header.ReadFromFile(fin);
    MY_PROCESS_ERROR(nRetCode);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int ZipTool::CopyF2F(FILE *fin, int all_in_length, FILE *fout)
{
    int nResult  = false;
    int nRetCode = false;

    Byte in_buffer[1024];
    int read_count = 0;

    while (read_count < all_in_length)
    {
        int will_read_length = all_in_length - read_count;

        if (will_read_length > MY_SIZE_OF_ARRAY(in_buffer))
        {
            will_read_length = MY_SIZE_OF_ARRAY(in_buffer);
        }

        int actual_read_count = fread(in_buffer, 1, will_read_length, fin);
        MY_PROCESS_ERROR(actual_read_count == will_read_length);

        read_count += actual_read_count;

        nRetCode = fwrite(in_buffer, 1, actual_read_count, fout);
        MY_PROCESS_ERROR(nRetCode >= actual_read_count);
    }

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}
