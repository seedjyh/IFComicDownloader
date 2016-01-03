//
//   File name      : CodeTransfromer.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : FindNoServerLite
//
//   Create datetime: 2010-10-29 11:32:45
//

// Tested or implemented header
#include "CodeTransformer.h"

// C system headers
#include <math.h>
#include <windows.h>
#include <assert.h>

// C++ system headers
// ...

// Headers from other projects
#include "IFMacros/BasicMacro.h"

// Headers of current project
// ...

int CodeTransformer::Trans7BitTo8Bit(const string &kSrcStr, string &dst_str)
{
    int nResult  = false;
    int nRetCode = false;

    string strResult;
    size_t u7bitStrLen = 0;
    size_t u8bitStrLen = 0;
    unsigned char byBitTest;

    u7bitStrLen = kSrcStr.size();

    // ¼ì²â´íÎó
    byBitTest = 0x80;
    for (int i = 7; i >= 8 - (int)(u7bitStrLen % 7); i--, byBitTest >>= 1)
    {
        MY_PROCESS_ERROR( !(kSrcStr[kSrcStr.size() - 1] & byBitTest) );
    }

    // ×ª»»
    strResult.resize(kSrcStr.size() * 2);
    u8bitStrLen = 0;
    for (int i = 0; i < (int)kSrcStr.size(); i++)
    {
        int nRemainder = i % 7;
        if (0 == nRemainder)
        {
            strResult[u8bitStrLen] = kSrcStr[i] & 127;
            u8bitStrLen++;
            continue;
        }

        strResult[u8bitStrLen] = (((unsigned char)kSrcStr[i]) & ((1 << (7 - nRemainder) ) - 1) ) << nRemainder;
        strResult[u8bitStrLen] |= ((unsigned char)kSrcStr[i - 1]) >> (8 - nRemainder) ;
        u8bitStrLen++;

        if (6 == nRemainder)
        {
            strResult[u8bitStrLen] = kSrcStr[i] >> 1;
            u8bitStrLen++;
        }

        if (
            (i == kSrcStr.size() - 1) &&
            (nRemainder != 6)
        )
        {
            MY_PROCESS_ERROR(!(kSrcStr[i] >> (7 - nRemainder)) );
        }
    }

    strResult.resize(u8bitStrLen);

// Exit1:
    dst_str = strResult;
    nResult = true;
Exit0:
    return nResult;
}

//////////////////////////////////////////////////////////////////////////
//
// GSM 03.38 version 5.6.0
// chapter: 6.1.2.1.1 Packing of 7-bit characters
//
int CodeTransformer::Trans8BitTo7Bit(const string &kSrcStr, string &dst_str)
{
    int nResult  = false;
    int nRetCode = false;

    dst_str = string( (size_t)ceil(kSrcStr.size() * 7.0 / 8.0), '\0');

    for (size_t i = 0; i < kSrcStr.size(); i++)
    {
        size_t complete_chunk_count = i / 8;
        size_t lowest_bit_offset    = 7 - (i + 7) % 8;
        size_t lowest_octet_index   = static_cast<size_t>( (i % 8) - 0.1);

        MY_PROCESS_ERROR(0 == (kSrcStr[i] & 0x80) );

        dst_str[7 * complete_chunk_count + lowest_octet_index] |= static_cast<char>(kSrcStr[i] << lowest_bit_offset);
        if (
            (lowest_bit_offset != 0) &&
            (lowest_bit_offset != 1)
        )
        {
            dst_str[7 * complete_chunk_count + lowest_octet_index + 1] |= static_cast<char>(kSrcStr[i] >> (8 - lowest_bit_offset) );
        }
    }

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int CodeTransformer::Trans8BitTo7BitWithFillBit(const string &kSrcStr, string &dst_str)
{
    int nResult  = false;
    int nRetCode = false;

    string tail_8bit = string(kSrcStr, 1, kSrcStr.size() -1);
    string tail_7bit;

    nRetCode = Trans8BitTo7Bit(tail_8bit, tail_7bit);
    MY_PROCESS_ERROR(nRetCode);

    dst_str.resize(1);
    dst_str[0] = (kSrcStr[0] << 1) & 0xFE;
    dst_str += tail_7bit;

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}


int CodeTransformer::AllAscII(const string &kStr)
{
    int nResult  = false;
    int nRetCode = false;

    for (size_t i = 0; i < kStr.size(); i++)
    {
        MY_PROCESS_ERROR(!(kStr[i] & 0x80) );
    }

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

char CodeTransformer::IntToHex(unsigned int number)
{
    if (number < 10)
    {
        return '0' + number;
    }

    if (number < 16)
    {
        return 'A' + (number - 10);
    }

    return '\0';
}

int CodeTransformer::HexToInt(char number)
{
    if ('0' <= number && number <= '9')
    {
        return number - '0';
    }

    if ('A' <= number && number <= 'F')
    {
        return number - 'A' + 10;
    }

    if ('a' <= number && number <= 'f')
    {
        return number - 'a' + 10;
    }

    return -1;
}


string CodeTransformer::TransByteToHex(const string &kSrcStr)
{
    string result;

    result.resize(kSrcStr.size() * 3 - 1); // "83 82 81" from "321", length = 3 * 3 - 1 = 8

    for (size_t i = 0, j = 0; i < kSrcStr.size(); i++)
    {
        unsigned char current_byte = kSrcStr[i];
        if (i > 0)
        {
            result[j++] = ' ';
        }

        result[j++] = IntToHex(current_byte >> 4);
        result[j++] = IntToHex(current_byte & 0x0F);
    }

    return result;
}

size_t CodeTransformer::Get7BitLength(size_t len_of_8bit)
{
    size_t len_of_7bit = len_of_8bit * 7 / 8;

    if (len_of_8bit % 8 != 0)
    {
        len_of_7bit++;
    }

    return len_of_7bit;
}

size_t CodeTransformer::Get8BitOctetCount(size_t len_of_7bit)
{
    return len_of_7bit * 8 / 7;
}

int CodeTransformer::TransCharToTchar(size_t char_len, const char kCharStr[], size_t tchar_buf_size, TCHAR tchar_buf[])
{
    int nResult  = -1;
    int nRetCode = 0;

    int tchar_len = 0;
#if defined _UNICODE
    wchar_t wcNowWchar  = 0;
    for (size_t i = 0; i < static_cast<int>(char_len) && tchar_len < static_cast<int>(tchar_buf_size);)
    {
        if (tchar_len >= static_cast<int>(tchar_buf_size))
        {
            break;
        }

        nRetCode = mbtowc(&wcNowWchar, kCharStr + i, MB_CUR_MAX);
        // MY_PROCESS_ERROR(nRetCode >= 0);
        if (nRetCode < 0)
        {
            goto Exit0;
        }
        tchar_buf[tchar_len++] = wcNowWchar;
        i += nRetCode;
    }
#else
    tchar_len = char_len;
    if (tchar_len >= tchar_buf_size)
    {
        tchar_len = tchar_buf_size - 1;
    }
    strncpy(tchar_buf, kCharStr, tchar_len);
    
#endif
// Exit1:
    nResult = tchar_len;
Exit0:
    return tchar_len;
}

int CodeTransformer::TransCharToTchar(const string &kCharStr, size_t tchar_buf_size, TCHAR tchar_buf[])
{
    return TransCharToTchar(kCharStr.size(), kCharStr.c_str(), tchar_buf_size, tchar_buf);
}

int CodeTransformer::TransStringToTString(const string &kSrc, Tstring &ret_dst)
{
    int nResult  = false;
    int nRetCode = false;

    int buffer_size = kSrc.size() + 1;
    TCHAR *buffer = new TCHAR[buffer_size];
    MY_PROCESS_ERROR(buffer != NULL);

    nRetCode = TransCharToTchar(kSrc, buffer_size, buffer);
    MY_PROCESS_ERROR(nRetCode >= 0);
    buffer[buffer_size - 1] = TEXT('\0');
    if (nRetCode < buffer_size)
    {
        buffer[nRetCode] = TEXT('\0');
    }

    ret_dst = Tstring(buffer);

// Exit1:
    nResult = true;
Exit0:
    MY_DELETEARRAY(buffer);
    return nResult;
}

Tstring CodeTransformer::TransStringToTString(const string &kSrc)
{
    Tstring result;
    assert(TransStringToTString(kSrc, result));
    return result;
}

int CodeTransformer::TransTcharToChar(size_t tchar_len, const TCHAR kTcharBuf[], size_t char_buf_size, char char_buf[])
{
    int nResult  = false;
    int nRetCode = false;


    WideCharToMultiByte(CP_OEMCP, NULL, kTcharBuf, -1, char_buf, char_buf_size, NULL, FALSE);

// Exit1:
    nResult = true;
// Exit0:
    return nResult;
}


int CodeTransformer::TransTstringToString(const Tstring &kSrc, std::string &ret_dst)
{
    int nResult  = false;
    int nRetCode = false;

    char *buffer = NULL;
    int buffer_size = kSrc.size() * 2 + 1;

    buffer = new char[buffer_size];
    MY_PROCESS_ERROR(buffer);

    nRetCode = TransTcharToChar(kSrc.length(), kSrc.c_str(), buffer_size, buffer);
    MY_PROCESS_ERROR(nRetCode);

    ret_dst = std::string(buffer);

// Exit1:
    nResult = true;
Exit0:
    MY_DELETEARRAY(buffer);
    return nResult;
}

std::string CodeTransformer::TransTstringToString(const Tstring &kSrc)
{
    std::string result;
    assert(TransTstringToString(kSrc, result));
    return result;
}

int CodeTransformer::FormatUrltoUtf8(const string &kOriginalURL, string &ret_URL)
{
    int nResult  = false;
    int nRetCode = false;

    size_t uWriteCount = 0;

    wchar_t wcszBuffer[1024];
    size_t  uwcszBufferLen = 0;

    char   szUTF8Str[1024];
    size_t uUTF8StrLen = 0;

    nRetCode = MultiByteToWideChar(
        CP_ACP,
        MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
        kOriginalURL.c_str(),
        -1,
        wcszBuffer,
        sizeof(wcszBuffer) / sizeof(wcszBuffer[0])
    );
    MY_PROCESS_ERROR(nRetCode);
    uwcszBufferLen = nRetCode;

    nRetCode = WideCharToMultiByte(
        CP_UTF8,
        0,
        wcszBuffer,
        -1,
        szUTF8Str,
        sizeof(szUTF8Str) / sizeof(szUTF8Str[0]),
        NULL,
        NULL
    );
    MY_PROCESS_ERROR(nRetCode);
    uUTF8StrLen = nRetCode;

    ret_URL.clear();
    for (int i = 0; i < (int)uUTF8StrLen ; i++)
    {
        if ( (szUTF8Str[i] >> 7) & 1) // single UTF-8
        {
            // multi UTF-8
            ret_URL += '%';
            ret_URL += IntToHex( (szUTF8Str[i] >> 4) & 15 );
            ret_URL += IntToHex(szUTF8Str[i] & 15);
            continue;
        }

        if (' ' == szUTF8Str[i])
        {
            ret_URL += '%';
            ret_URL += IntToHex( (szUTF8Str[i] >> 4) & 15 );
            ret_URL += IntToHex(szUTF8Str[i] & 15);
            continue;
        }

        ret_URL += szUTF8Str[i];
    }

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int CodeTransformer::TransUtf8ToAnsi(const string &kOriginalURL, string &ret_URL) // TODO: URL => str
{
    int nResult  = false;
    int nRetCode = false;

    size_t uWriteCount = 0;

    wchar_t wcszBuffer[32768];
    size_t  uwcszBufferLen = 0;

    char   szUTF8Str[65536];
    size_t uUTF8StrLen = 0;

    nRetCode = MultiByteToWideChar(
        CP_UTF8,
        MB_ERR_INVALID_CHARS,
        kOriginalURL.c_str(),
        -1,
        wcszBuffer,
        sizeof(wcszBuffer) / sizeof(wcszBuffer[0])
    );
    MY_PROCESS_ERROR(nRetCode);
    nRetCode = GetLastError();
    uwcszBufferLen = nRetCode;

    nRetCode = WideCharToMultiByte(
        CP_ACP,
        0,
        wcszBuffer,
        -1,
        szUTF8Str,
        sizeof(szUTF8Str) / sizeof(szUTF8Str[0]),
        NULL,
        NULL
    );
    MY_PROCESS_ERROR(nRetCode);
    uUTF8StrLen = nRetCode;

    ret_URL = string(szUTF8Str);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int CodeTransformer::TransBigEndianUnicodeToAnsi(int original_str_length, const char kOriginalStr[], string &ansi_str)
{
    int nResult  = false;
    int nRetCode = false;

    MY_PROCESS_ERROR(0 == original_str_length % 2);

    size_t uWriteCount = 0;

    wchar_t wcszBuffer[32768] = {'\0'};
    size_t  uwcszBufferLen = 0;

    char   szAnsiStr[65536];
    size_t uAnsiStrLen = 0;

    uwcszBufferLen = 0;
    for (int i = 0; i < original_str_length; i+=2)
    {
        wcszBuffer[uwcszBufferLen++] = (kOriginalStr[i] << 8) | ((unsigned char)kOriginalStr[i + 1]);
    }

    nRetCode = WideCharToMultiByte(
        CP_ACP,
        0,
        wcszBuffer,
        -1,
        szAnsiStr,
        sizeof(szAnsiStr) / sizeof(szAnsiStr[0]),
        NULL,
        NULL
    );
    MY_PROCESS_ERROR(nRetCode);
    uAnsiStrLen = nRetCode;

    ansi_str.assign(szAnsiStr);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int CodeTransformer::TransCode(const string &kOriginalStr, unsigned int original_code_page, unsigned int result_code_page, string &ret_result)
{
    int nRetCode = false;
    int nResult  = false;

    size_t uWriteCount = 0;

    wchar_t wcszBuffer[32768];
    size_t  uwcszBufferLen = 0;

    char   result_buffer[65536];
    size_t result_length = 0;

    int flag = MB_ERR_INVALID_CHARS;

    nRetCode = MultiByteToWideChar(
        original_code_page,
        flag,
        kOriginalStr.c_str(),
        -1,
        wcszBuffer,
		MY_SIZE_OF_ARRAY(wcszBuffer)
    );
    MY_PROCESS_ERROR(nRetCode);
    nRetCode = GetLastError();
    uwcszBufferLen = nRetCode;

    nRetCode = WideCharToMultiByte(
        result_code_page,
        0,
        wcszBuffer,
        -1,
        result_buffer,
		MY_SIZE_OF_ARRAY(result_buffer),
        NULL,
        NULL
    );
    MY_PROCESS_ERROR(nRetCode);
    result_length = nRetCode;

    ret_result = string(result_buffer);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}
