//
//   File name      : PythonFunction.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-03 21:48:15
//

// Inherited header
#include "PythonFunction.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <Python.h>

// Headers of current project
#include "IFDataType/DataHolder.h"

int PythonFunction::Add(int a, int b)
{
    PyObject *main_module = PyImport_ImportModule("__main__");
    PyObject *main_dict = PyModule_GetDict(main_module);

    PyObject *a_obj = PyInt_FromLong(a);
    PyDict_SetItemString(main_dict, "a", a_obj);

    PyObject *b_obj = PyInt_FromLong(b);
    PyDict_SetItemString(main_dict, "b", b_obj);

    PyRun_SimpleString("sum = a + b");

    PyObject *sum_obj = PyMapping_GetItemString(main_dict, "sum");
    return PyInt_AsLong(sum_obj);
}

void PythonFunction::DES_Decrypt_ECB_PKCS5(const DataHolder &kCiphertext, DataHolder &kKey, DataHolder &ret_plaintext)
{
    PyObject *main_module = PyImport_ImportModule("__main__");
    PyObject *main_dict = PyModule_GetDict(main_module);

    PyObject *key_obj = PyString_FromStringAndSize(kKey.content(), kKey.size());
    PyDict_SetItemString(main_dict, "key", key_obj);

    PyRun_SimpleString("import pyDes");
    PyRun_SimpleString("decrypter = pyDes.des(key, pyDes.ECB, b\"\\0\\0\\0\\0\\0\\0\\0\\0\", pad=None, padmode=pyDes.PAD_PKCS5)");

    PyObject *ciphertext_obj = PyString_FromStringAndSize(kCiphertext.content(), kCiphertext.size());
    PyDict_SetItemString(main_dict, "ciphertext", ciphertext_obj);
    PyRun_SimpleString("plaintext = decrypter.decrypt(ciphertext)");

    PyObject *plaintext_obj = PyMapping_GetItemString(main_dict, "plaintext");

    char *pt = NULL;
    Py_ssize_t pt_len = 0;
    int ret = PyString_AsStringAndSize(plaintext_obj, &pt, &pt_len);
    ret_plaintext.Append(pt_len, pt);
    return;
}
