//
//   File name      : DesDecrypter.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : DesTool
//
//   Create datetime: 2014-05-28 15:47:01
//

// Tested or implemented header
#include "DesDecrypter.h"

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

DesDecrypter::DesDecrypter(const char kKey[])
{
    assert(kKey != NULL);

    int key_length = strlen(kKey);
    assert(key_length <= 7);
    memset(key_, 0, sizeof(key_) );
    strcpy(key_, kKey);
}

DesDecrypter::~DesDecrypter()
{
}

void DesDecrypter::Decrypt(
    const char kCiphertext[],
    int        /*plaintext_buffer_size*/,
    char       ret_plaintext_buffer[]
)
{
    int ret_code = DES_Decrypt(
        const_cast<char*>(kCiphertext),
        key_,
        ret_plaintext_buffer
    );
    assert(ret_code);

    return;
}

