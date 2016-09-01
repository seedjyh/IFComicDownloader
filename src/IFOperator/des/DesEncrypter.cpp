//
//   File name      : DesEncrypter.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : DesTool
//
//   Create datetime: 2014-05-27 16:51:18
//

// Tested or implemented header
#include "DesEncrypter.h"

// C system headers
#include <assert.h>
#include <stddef.h>
#include <string.h>

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
extern "C"{
#include "des.h"
}

DesEncrypter::DesEncrypter(const char kKey[])
{
    assert(kKey != NULL);

    int key_length = strlen(kKey);
    assert(key_length <= 7);
    memset(key_, 0, sizeof(key_) );
    strcpy(key_, kKey);
}

DesEncrypter::~DesEncrypter()
{
}

void DesEncrypter::Encrypt(
    const char kPlaintext[],
    int   /*ciphertext_buffer_size*/,
    char  ret_ciphertext_buffer[]
)
{
    int ret_code = DES_Encrypt(
        const_cast<char*>(kPlaintext),
        key_,
        ret_ciphertext_buffer
    );
    assert(ret_code);

    return;
}

