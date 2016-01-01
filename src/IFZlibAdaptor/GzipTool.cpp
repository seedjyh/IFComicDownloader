//
//   File name      : GzipTool.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFZlibAdaptor
//
//   Create datetime: 2012-10-04 14:16:28
//

// Tested or implemented header
#include "GzipTool.h"

// C system headers
#include <string.h>
#include <stdio.h>
#include <assert.h>

// C++ system headers
// ...

// Headers from other projects
#include "IFDataType/DataHolder.h"
#include "zlib.h"

// Headers of current project
// ...

const static int segment_size = 1460;
int GzipTool::Unzip(int source_len, const char kSource[], DataHolder &ret_result)
{
    int ret,have;
    int offset=0;
    z_stream d_stream;
    Byte uncompr[segment_size*4]={0};
    uLong comprLen, uncomprLen;
    comprLen =source_len;//һ��ʼд����comprlen=sizeof(compr)�Լ�comprlen=strlen(compr)���������ֶ����ԡ�

    //sizeof(compr)��Զ����segment_size����Ȼ���ԣ�strlen(compr)Ҳ�ǲ��Եģ���Ϊstrlenֻ�㵽֮ǰ��

    //����gzip����zlib������ܶࡣ
    uncomprLen = segment_size*4;
    strcpy((char*)uncompr, "garbage");

    d_stream.zalloc = Z_NULL;
    d_stream.zfree = Z_NULL;
    d_stream.opaque = Z_NULL;

    d_stream.next_in = Z_NULL;//inflateInit��inflateInit2�������ʼ��next_in��avail_in
    d_stream.avail_in = 0;//deflateInit��deflateInit2����

    ret = inflateInit2(&d_stream,47);
    if(ret!=Z_OK)
    {
        printf("inflateInit2 error:%d",ret);
        return ret;
    }
    d_stream.next_in=reinterpret_cast<Bytef*>(const_cast<char*>(kSource) );
    d_stream.avail_in=comprLen;
    do
    {
        d_stream.next_out=uncompr;
        d_stream.avail_out=uncomprLen;
        ret = inflate(&d_stream,Z_NO_FLUSH);
        assert(ret != Z_STREAM_ERROR);
        switch (ret)
        {
        case Z_NEED_DICT:
            ret = Z_DATA_ERROR;
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            (void)inflateEnd(&d_stream);
            return ret;
        }
        have=uncomprLen-d_stream.avail_out;
        ret_result.Append(have, (const char*)uncompr);

        offset+=have;

    }while(d_stream.avail_out==0);
    inflateEnd(&d_stream);
    return ret;
}

