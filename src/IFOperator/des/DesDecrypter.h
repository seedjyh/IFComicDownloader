//
//   File name      : DesDecrypter.h
//
//   Code by        : jiangyonghang
//
//   Project name   : DesTool
//
//   Create datetime: 2014-05-28 15:36:45
//

#ifndef _DESTOOL_INCLUDE_DESDECRYPTER_H_
#define _DESTOOL_INCLUDE_DESDECRYPTER_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class DesDecrypter
{
    char key_[8];
public:
    DesDecrypter(const char kKey[]);
    virtual ~DesDecrypter();

    void Decrypt(
        const char kCiphertext[],
        int        plaintext_buffer_size,
        char       ret_plaintext_buffer[]
    );

protected:
private:
};

#endif

