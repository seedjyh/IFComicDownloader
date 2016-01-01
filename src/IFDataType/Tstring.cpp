//
//   File name      : Tstring.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2011-03-23 00:26:23
//

// Tested or implemented header
#include "Tstring.h"

// C system headers
#include <assert.h>

// C++ system headers
// ...

// Headers from other projects
#include "IFMacros/BasicOperateMacro.h"

// Headers of current project
// ...

static const int s_kInitialBufferSize = 256;

static int GetProperSize(int content_length)
{
    int result = 1;

    while (result <= content_length)
    {
        result <<= 1;
    }

    return result;
}

static void ExpandBufferFillBlank(int &buffer_size, TCHAR *&buffer, int new_size)
{
    assert(new_size >= buffer_size);

    TCHAR *old_buffer = buffer;
    buffer = NULL;

    buffer_size = GetProperSize(new_size);
    assert(buffer_size > new_size);
    buffer = new TCHAR[buffer_size];
    assert(buffer);

    memset(buffer, 0, sizeof(buffer[0]) * buffer_size);

    MY_DELETEARRAY(old_buffer);

    return;
}

static void ExpandBufferWithContent(int &buffer_size, TCHAR *&buffer, int new_size)
{
    assert(new_size >= buffer_size);

    TCHAR *old_buffer = buffer;
    buffer = NULL;

    ExpandBufferFillBlank(buffer_size, buffer, new_size);
    _tcscpy(buffer, old_buffer);

    MY_DELETEARRAY(old_buffer);

    return;
}

Tstring::Tstring()
:   buffer_size_(0),
    buffer_(NULL),
    content_length_(0){
    buffer_size_ = s_kInitialBufferSize;
    buffer_ = new TCHAR[buffer_size_];
    memset(buffer_, 0, sizeof(buffer_[0]) * buffer_size_);
}

Tstring::Tstring(const TCHAR kStr[])
:   buffer_size_(0),
    buffer_(NULL),
    content_length_(0){
    assert(kStr);
    int source_length = _tcslen(kStr);
    buffer_size_ = GetProperSize(source_length);
    buffer_ = new TCHAR[buffer_size_];
    memset(buffer_, 0, sizeof(buffer_[0]) * buffer_size_);
    _tcscpy(buffer_, kStr);
    content_length_ = source_length;
}

Tstring::Tstring(const Tstring &kStr)
:   buffer_size_(0),
    buffer_(NULL),
    content_length_(0){
    buffer_size_ = GetProperSize(kStr.content_length_);
    buffer_ = new TCHAR[buffer_size_];
    memset(buffer_, 0, sizeof(buffer_[0]) * buffer_size_);
    _tcscpy(buffer_, kStr.buffer_);
    content_length_ = kStr.content_length_;
}

Tstring::~Tstring()
{
    MY_DELETEARRAY(buffer_);
}

const TCHAR* Tstring::c_str() const
{
    return buffer_;
}

int Tstring::length() const
{
    return content_length_;
}

int Tstring::size() const
{
    return content_length_;
}

void Tstring::resize(int new_size)
{
    if (new_size < content_length_)
    {
        buffer_[new_size] = TCHAR('\0');
    }
    else
    {
        if (new_size >= buffer_size_)
        {
            ExpandBufferWithContent(buffer_size_, buffer_, new_size);
        }
    }

    content_length_ = new_size;

    return;
}

void Tstring::clear()
{
    memset(buffer_, 0, sizeof(buffer_[0]) * buffer_size_ );
    content_length_ = 0;

    return;
}

void Tstring::assign(const TCHAR kStr[])
{
    assert(kStr != NULL);
    int kstr_length = _tcslen(kStr);
    int min_size = GetProperSize(kstr_length);
    if (buffer_size_ < min_size)
    {
        ExpandBufferFillBlank(buffer_size_, buffer_, min_size);
    }
    content_length_ = kstr_length;
    _tcscpy(buffer_, kStr);
    return;
}

bool Tstring::operator==(const Tstring &kStr) const
{
    return (0 == _tcscmp(buffer_, kStr.buffer_) );
}

Tstring& Tstring::operator=(const Tstring &kStr)
{
    assign(kStr.c_str() );
    return *this;
}

Tstring& Tstring::operator+=(TCHAR new_char)
{
    if (content_length_ + 1 >= buffer_size_)
    {
        ExpandBufferWithContent(buffer_size_, buffer_, content_length_ + 1);
    }
    buffer_[content_length_] = new_char;
    content_length_++;

    return *this;
}

Tstring& Tstring::operator+=(const TCHAR kTail[])
{
    int tail_length = _tcslen(kTail);

    if (content_length_ + tail_length >= buffer_size_)
    {
        ExpandBufferWithContent(buffer_size_, buffer_, content_length_ + tail_length);
    }
    _tcscpy(buffer_ + content_length_ , kTail);
    content_length_ += tail_length;

    return *this;
}

Tstring& Tstring::operator+=(const Tstring &kTail)
{
    if (content_length_ + kTail.content_length_ >= buffer_size_)
    {
        ExpandBufferWithContent(buffer_size_, buffer_, content_length_ + kTail.content_length_);
    }
    memcpy(buffer_ + content_length_, kTail.buffer_, sizeof(buffer_[0]) * kTail.content_length_);
    content_length_ += kTail.content_length_;

    return *this;
}

TCHAR& Tstring::operator[](int index)
{
    assert(index >= 0);
    assert(index < content_length_);
    return buffer_[index];
}

const TCHAR& Tstring::operator[](int index) const
{
    assert(index >= 0);
    assert(index < content_length_);
    return buffer_[index];
}

Tstring operator+(const Tstring &kHead, const TCHAR kTail[])
{
    Tstring result(kHead);

    result += kTail;

    return result;
}

Tstring operator+(const TCHAR kHead[], const Tstring kTail)
{
    Tstring result(kHead);

    result += kTail;

    return result;
}


Tstring operator+(const Tstring kHead, const Tstring kTail)
{
    Tstring result(kHead);

    result += kTail;

    return result;
}
