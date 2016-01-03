//
//   File name      : CodeTransformer.h
//
//   Code by        : jiangyonghang
//
//   Project name   : FindNoServerLite
//
//   Create datetime: 2010-10-29 11:24:44
//

#ifndef _FINDNOSERVERLITE_CODETRANSFORMER_H_
#define _FINDNOSERVERLITE_CODETRANSFORMER_H_ 1

// Tested or implemented header
// ...

// C system headers
#include <tchar.h>

// C++ system headers
#include <string>
using namespace std;

// Headers from other projects
#include "IFDataType/Tstring.h"

// Headers of current project
// ...

class CodeTransformer
{
public:
    // 将7-bit打包后的字符串解包成8bit的格式。
    // 返回 true  一切顺利
    //      false 7-bit编码不符合规范，通常是最后一个字节的需要填0的bit没有按规则填0。
    static int Trans7BitTo8Bit(const string &kSrcStr, string &dst_str);

    // 将8bit的字符串压缩成7bit的格式。
    // 要求8bit串里均为ASCII字符。
    // 最后字符可能是不完整的，在高bit填0。
    // 返回 true  一切顺利
    //      false 8-bit串里出现非法字符（即最高bit位不是0的字符）
    static int Trans8BitTo7Bit(const string &kSrcStr, string &dst_str);

    // 将8bit的字符串转成7bit格式，但考虑填充位（fill bit）
    // 要求8bit串里均为ASCII字符。
    // 填充位的规范：7bit字符串的最后字节都是完整的字符。如果有多余bit位，提前到第一个字节的低bit上。
    static int Trans8BitTo7BitWithFillBit(const string &kSrcStr, string &dst_str);

    static int AllAscII(const string &kStr);

    static char IntToHex(unsigned int number);

    static int HexToInt(char number);

    static string TransByteToHex(const string &kSrcStr);

    // 计算指定数量的8bit字符需要多长的7bit编码缓冲区才能存下
    static size_t Get7BitLength(size_t len_of_8bit);

    // 计算指定字节数的7bit编码缓冲区能存储几个完整的8bit字符
    static size_t Get8BitOctetCount(size_t len_of_7bit);

    // 将char型字符串转成TCHAR型
    static int TransCharToTchar(size_t char_len, const char kCharStr[], size_t tchar_buf_size, TCHAR tchar_buf[]);
    static int TransCharToTchar(const string &kCharStr, size_t tchar_buf_size, TCHAR tchar_buf[]);
    static int TransStringToTString(const string &kSrc, Tstring &ret_dst);
    static Tstring TransStringToTString(const string &kSrc);

    static int TransTcharToChar(size_t tchar_len, const TCHAR kTcharBuf[], size_t char_buf_size, char char_buf[]);

    static int TransTstringToString(const Tstring &kSrc, std::string &ret_dst);
    static std::string TransTstringToString(const Tstring &kSrc);

    static int FormatUrltoUtf8(const string &kOriginalURL, string &ret_URL);

    static int TransUtf8ToAnsi(const string &kOriginalStr, string &ansi_str);

    static int TransBigEndianUnicodeToAnsi(int original_str_length, const char kOriginalStr[], string &ansi_str);

	static int TransCode(const string &kOriginalStr, unsigned int original_code_page, unsigned int result_code_page, string &ret_result);

protected:
private:
    CodeTransformer(){};
    ~CodeTransformer(){};
};

#endif
