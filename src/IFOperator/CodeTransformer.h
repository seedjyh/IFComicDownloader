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
    // ��7-bit�������ַ��������8bit�ĸ�ʽ��
    // ���� true  һ��˳��
    //      false 7-bit���벻���Ϲ淶��ͨ�������һ���ֽڵ���Ҫ��0��bitû�а�������0��
    static int Trans7BitTo8Bit(const string &kSrcStr, string &dst_str);

    // ��8bit���ַ���ѹ����7bit�ĸ�ʽ��
    // Ҫ��8bit�����ΪASCII�ַ���
    // ����ַ������ǲ������ģ��ڸ�bit��0��
    // ���� true  һ��˳��
    //      false 8-bit������ַǷ��ַ��������bitλ����0���ַ���
    static int Trans8BitTo7Bit(const string &kSrcStr, string &dst_str);

    // ��8bit���ַ���ת��7bit��ʽ�����������λ��fill bit��
    // Ҫ��8bit�����ΪASCII�ַ���
    // ���λ�Ĺ淶��7bit�ַ���������ֽڶ����������ַ�������ж���bitλ����ǰ����һ���ֽڵĵ�bit�ϡ�
    static int Trans8BitTo7BitWithFillBit(const string &kSrcStr, string &dst_str);

    static int AllAscII(const string &kStr);

    static char IntToHex(unsigned int number);

    static int HexToInt(char number);

    static string TransByteToHex(const string &kSrcStr);

    // ����ָ��������8bit�ַ���Ҫ�೤��7bit���뻺�������ܴ���
    static size_t Get7BitLength(size_t len_of_8bit);

    // ����ָ���ֽ�����7bit���뻺�����ܴ洢����������8bit�ַ�
    static size_t Get8BitOctetCount(size_t len_of_7bit);

    // ��char���ַ���ת��TCHAR��
    static int TransCharToTchar(size_t char_len, const char kCharStr[], size_t tchar_buf_size, TCHAR tchar_buf[]);
    static int TransCharToTchar(const string &kCharStr, size_t tchar_buf_size, TCHAR tchar_buf[]);
    static int TransStringToTString(const string &kSrc, Tstring &ret_dst);

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
