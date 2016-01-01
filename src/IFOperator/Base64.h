/*
*    File name      : Base64.h
*
*    Code by        : jiangyonghang
*
*    Project name   : Base64
*
*    Create datetime: 2010-09-09 06:08:9
*/

#ifndef _BASE64_BASE64_H_
#define _BASE64_BASE64_H_ 1

#include <string>
using namespace std;

class Base64
{
public:
    static int Encoding(const string &cstrPlainText, string &strRetCipherText);
    static int Decode(const string &cstrCipherText, string &strRetPlainText);

    //如果遇到等号，则按连续等号的最后一个等号为子串末尾进行分割-解码-合并
    static int SuperDecoding(const string &cstrCipherText, string &strRetPlainText);
protected:
private:
    Base64();
    ~Base64();
    static int  CharToInt(char chBase64Char);
    static char IntToChar(int nBase64Int);
};

#endif
