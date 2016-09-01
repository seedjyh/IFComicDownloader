//
//   File name      : DesEncrypter.h
//
//   Code by        : jiangyonghang
//
//   Project name   : DesTool
//
//   Create datetime: 2014-05-27 16:42:24
//

#ifndef _DESTOOL_INCLUDE_DESENCRYPTER_H_
#define _DESTOOL_INCLUDE_DESENCRYPTER_H_ 1

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

class DesEncrypter
{
    char key_[8];
public:
    DesEncrypter(const char kKey[]);
    virtual ~DesEncrypter();

    void Encrypt(
        const char kPlaintext[],
        int        ciphertext_buffer_size,
        char       ret_ciphertext_buffer[]
    );

protected:
private:
};

#endif

