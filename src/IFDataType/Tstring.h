//
//   File name      : Tstring.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2011-03-23 00:25:23
//

#ifndef _IFDATATYPE_SRC_TSTRING_H_
#define _IFDATATYPE_SRC_TSTRING_H_ 1

// Tested or implemented header
// ...

// C system headers
#include <tchar.h>

// C++ system headers
#include <string>

// Headers from other projects
#include "IFMacros/DevelopMacros.h"

// Headers of current project
// ...

class Tstring // 可以用new数组而不是定长数组
{
    int buffer_size_;
    TCHAR *buffer_;
    int content_length_;
public:
    Tstring();
    Tstring(const TCHAR kStr[]);
    Tstring(const Tstring &kStr);
    ~Tstring();

    const TCHAR* c_str() const;

    int length() const;
    int size() const;
    void resize(int new_size);
    void clear();
    void assign(const TCHAR kStr[]);

    bool operator==(const Tstring &kStr) const;

    Tstring& operator=(const Tstring &kStr);

    Tstring& operator+=(TCHAR new_char);

    Tstring& operator+=(const TCHAR kTail[]);

    Tstring& operator+=(const Tstring &kTail);

    TCHAR& operator[](int index);

    const TCHAR& operator[](int index) const;

    friend Tstring operator+(const Tstring &kHead, const TCHAR kTail[]);

    friend Tstring operator+(const TCHAR kHead[], const Tstring kTail);

    friend Tstring operator+(const Tstring kHead, const Tstring kTail);
protected:
private:
};

#endif
