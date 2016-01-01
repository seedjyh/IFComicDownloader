/*
*    File name      : Base64.cpp
*
*    Code by        : jiangyonghang
*
*    Project name   : Base64
*
*    Create datetime: 2010-09-09 06:05:9
*/

#include "Base64.h"
#include <assert.h>
#include <vector>
#include "IFMacros/BasicMacro.h"
using namespace std;


int Base64::CharToInt(char chBase64Char)
{
    int nWorkResult = 0;
    
    if (
        (chBase64Char >= 'A') &&
        (chBase64Char <= 'Z')
    )
    {
        nWorkResult = chBase64Char - 'A';
    }
    else if (
        (chBase64Char >= 'a') &&
        (chBase64Char <= 'z')
    )
    {
        nWorkResult = chBase64Char - 'a' + 26;
    }
    else if (
        (chBase64Char >= '0') &&
        (chBase64Char <= '9')
    )
    {
        nWorkResult = chBase64Char - '0' + 52;
    }
    else
    {
        switch (chBase64Char)
        {
        case '+':
            nWorkResult = 62;
            break;
        case '/':
            nWorkResult = 63;
            break;
        case '=':
            nWorkResult = 64;
            break;
        default:
            nWorkResult = -1;
        }
    }

    return nWorkResult;
}

char Base64::IntToChar(int nBase64Int)
{
    char chWorkResult = '\0';

    if (
        (nBase64Int >= 0) &&
        (nBase64Int <= 25 )
    )
    {
        chWorkResult = nBase64Int + 'A';
    }
    else if (
        (nBase64Int >= 26) &&
        (nBase64Int <= 51)
    )
    {
        chWorkResult = nBase64Int - 26 + 'a';
    }
    else if (
        (nBase64Int >= 52) &&
        (nBase64Int <= 61)
    )
    {
        chWorkResult = nBase64Int - 52 + '0';
    }
    else
    {
        switch (nBase64Int)
        {
        case 62:
            chWorkResult = '+';
            break;
        case 63:
            chWorkResult = '/';
            break;
        case 64:
            chWorkResult = '=';
            break;
        default:
            chWorkResult = '?';
        }
    }

    return chWorkResult;
}

int Base64::Encoding(const string &cstrPlainText, string &strRetCipherText)
{
    int nResult  = false;
    int nRetCode = false;

    size_t  uCipherTextBufSize     = 0;
    char   *pacCipherTextBuf       = NULL; // base64 string ends with '\0'.
    size_t  uCipherTextLen         = 0;

    uCipherTextBufSize = (cstrPlainText.size() / 3 + 1) * 4 + 1;
    pacCipherTextBuf = new char[uCipherTextBufSize];
    MY_PROCESS_ERROR(pacCipherTextBuf);

    uCipherTextLen    = 0;
    for (int i = 0; i < (int)cstrPlainText.size(); i += 3)
    {
        if ((int)cstrPlainText.size() - 1 >= i + 2) // 2 or more characters.
        {
            pacCipherTextBuf[uCipherTextLen    ] = IntToChar(                                                                  (((unsigned char)cstrPlainText[i    ]) >> 2));
            pacCipherTextBuf[uCipherTextLen + 1] = IntToChar(((((unsigned char)cstrPlainText[i    ]) & ((1 << 2) - 1)) << 4) | (((unsigned char)cstrPlainText[i + 1]) >> 4));
            pacCipherTextBuf[uCipherTextLen + 2] = IntToChar(((((unsigned char)cstrPlainText[i + 1]) & ((1 << 4) - 1)) << 2) | (((unsigned char)cstrPlainText[i + 2]) >> 6));
            pacCipherTextBuf[uCipherTextLen + 3] = IntToChar((((unsigned char)cstrPlainText[i + 2]) & ((1 << 6) - 1)));
            uCipherTextLen += 4;
            continue;
        }

        if ((int)cstrPlainText.size() - 1 == i + 1) // last 2 characters.
        {
            pacCipherTextBuf[uCipherTextLen    ] = IntToChar(                                                                  (((unsigned char)cstrPlainText[i    ]) >> 2));
            pacCipherTextBuf[uCipherTextLen + 1] = IntToChar(((((unsigned char)cstrPlainText[i    ]) & ((1 << 2) - 1)) << 4) | (((unsigned char)cstrPlainText[i + 1]) >> 4));
            pacCipherTextBuf[uCipherTextLen + 2] = IntToChar((((unsigned char)cstrPlainText[i + 1]) & ((1 << 4) - 1)) << 2);
            uCipherTextLen += 3;
            break;
        }

        if ((int)cstrPlainText.size() - 1 == i) // last 1 character.
        {
            pacCipherTextBuf[uCipherTextLen    ] = IntToChar(                                                                  (((unsigned char)cstrPlainText[i    ]) >> 2));
            pacCipherTextBuf[uCipherTextLen + 1] = IntToChar((((unsigned char)cstrPlainText[i    ]) & ((1 << 2) - 1)) << 4);
            uCipherTextLen += 2;
            break;
        }

        assert(false);
    }
    while (uCipherTextLen % 4)
    {
        pacCipherTextBuf[uCipherTextLen++] = '='; // (pad)
    }

    // check answer.
    for (int i = 0; i < (int)uCipherTextLen; i++)
    {
        assert(pacCipherTextBuf[i] != '?');
    }

// Exit1:
    pacCipherTextBuf[uCipherTextLen] = '\0'; // There's no '\0' in base64 string.
    strRetCipherText = string(pacCipherTextBuf);
    nResult = true;
Exit0:
    MY_DELETEARRAY(pacCipherTextBuf);
    return nResult;
}

int Base64::Decode(const string &cstrCipherText, string &strRetPlainText)
{
    int nResult  = false;
    int nRetCode = false;

    size_t       uPlainTextBufSize = 0;
    char        *pacPlainTextBuf   = NULL; // base64 string ends with '\0'.
    size_t       uPlainTextLen     = 0;
    
    vector <unsigned char> IntModeCipherText;

    MY_PROCESS_ERROR(0 == cstrCipherText.size() % 4);

    uPlainTextBufSize = cstrCipherText.size() / 4 * 3 + 1;
    pacPlainTextBuf   = new char[uPlainTextBufSize];
    MY_PROCESS_ERROR(pacPlainTextBuf);

    // translate and check.
    IntModeCipherText.clear();
    for (int i = 0; i < (int)cstrCipherText.size(); i++)
    {
        int nTemp = CharToInt(cstrCipherText[i]);
        MY_PROCESS_ERROR(nTemp >= 0);
        MY_PROCESS_ERROR(nTemp <= 64);
        if (64 == nTemp)
        {
            if ((int)cstrCipherText.size() - 2 == i)
            {
                MY_PROCESS_ERROR(64 == CharToInt(cstrCipherText[(int)cstrCipherText.size() - 1]));
                break;
            }
            MY_PROCESS_ERROR((int)cstrCipherText.size() - 1 == i);
            break;
        }

        IntModeCipherText.push_back(nTemp);
    }

    for (int i = 0; i < (int)IntModeCipherText.size(); i += 4)
    {
        if ((int)IntModeCipherText.size() - 1 >= i + 3) // 4 or more characters.
        {
            pacPlainTextBuf[uPlainTextLen    ] = (IntModeCipherText[i    ] << 2) | ((IntModeCipherText[i + 1] >> 4) &  3);
            pacPlainTextBuf[uPlainTextLen + 1] = (IntModeCipherText[i + 1] << 4) | ((IntModeCipherText[i + 2] >> 2) & 15);
            pacPlainTextBuf[uPlainTextLen + 2] = (IntModeCipherText[i + 2] << 6) | ( IntModeCipherText[i + 3]           );
            uPlainTextLen += 3;
            continue;
        }

        if ((int)IntModeCipherText.size() - 1 == i + 2) // last 3 characters.
        {
            MY_PROCESS_ERROR(!(IntModeCipherText[i + 2] & 3));
            pacPlainTextBuf[uPlainTextLen    ] = (IntModeCipherText[i    ] << 2) | ((IntModeCipherText[i + 1] >> 4) &  3);
            pacPlainTextBuf[uPlainTextLen + 1] = (IntModeCipherText[i + 1] << 4) | ((IntModeCipherText[i + 2] >> 2) & 15);
            uPlainTextLen += 2;
            break;
        }

        if ((int)IntModeCipherText.size() - 1 == i + 1) // last 2 character.
        {
            MY_PROCESS_ERROR(!(IntModeCipherText[i + 1] & 15));
            pacPlainTextBuf[uPlainTextLen    ] = (IntModeCipherText[i    ] << 2) | ((IntModeCipherText[i + 1] >> 4) & 3);
            uPlainTextLen++;
            break;
        }

        assert(false);
    }

// Exit1:
    strRetPlainText.resize(uPlainTextLen);
    for (int i = 0; i < (int)uPlainTextLen; i++)
    {
        strRetPlainText[i] = pacPlainTextBuf[i];
    }
    
    nResult = true;
Exit0:
    MY_DELETEARRAY(pacPlainTextBuf);
    return nResult;
}

int Base64::SuperDecoding(const string &cstrCipherText, string &strRetPlainText)
{
    int nResult  = false;
    int nRetCode = false;

    const char *kEqualMarkPos = NULL;
    const char *kCurrentBegin = NULL;
    vector <string> sub_string_list;

    sub_string_list.clear();

    kCurrentBegin = cstrCipherText.c_str();

    while (1)
    {
        kEqualMarkPos = strchr(kCurrentBegin, '=');
        if (!kEqualMarkPos)
        {
            sub_string_list.push_back(string(kCurrentBegin) );
            break;
        }

        while ('=' == *(kEqualMarkPos + 1) )
        {
            kEqualMarkPos++; 
        }

        sub_string_list.push_back(string(cstrCipherText, kCurrentBegin - cstrCipherText.c_str(), kEqualMarkPos - kCurrentBegin + 1) );

        kCurrentBegin = kEqualMarkPos + 1;
    }

    strRetPlainText.clear();

    for (size_t i = 0; i < sub_string_list.size(); i++)
    {
        string temp_result;

        nRetCode = Decode(sub_string_list[i], temp_result);
        MY_PROCESS_ERROR(nRetCode);

        strRetPlainText += temp_result;
    }

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

