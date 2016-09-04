//
//   File name      : PythonFunction.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-03 21:46:16
//

#ifndef _PYTHONFUNCTION_H_
#define _PYTHONFUNCTION_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class DataHolder;

class PythonFunction
{
public:
    static int Add(int a, int b);
    static void DES_Decrypt_ECB_PKCS5(const DataHolder &kCiphertext, DataHolder &kKey, DataHolder &ret_plaintext);
protected:
private:
    PythonFunction(){}
    ~PythonFunction(){}
};

#endif
