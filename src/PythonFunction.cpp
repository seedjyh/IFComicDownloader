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

    PyObject *a_obj = PyLong_FromLong(a);
    PyDict_SetItemString(main_dict, "a", a_obj);

    PyObject *b_obj = PyLong_FromLong(b);
    PyDict_SetItemString(main_dict, "b", b_obj);

    PyRun_SimpleString("sum = a + b");

    PyObject *sum_obj = PyMapping_GetItemString(main_dict, "sum");
    return PyLong_AsLong(sum_obj);
}

void PythonFunction::DES_Decrypt_ECB_PKCS5(const DataHolder &kCiphertext, DataHolder &kKey, DataHolder &ret_plaintext)
{
    PyObject *main_module = PyImport_ImportModule("__main__");
    PyObject *main_dict = PyModule_GetDict(main_module);

    PyObject *key_obj = PyBytes_FromStringAndSize(kKey.content(), kKey.size());
    PyDict_SetItemString(main_dict, "key", key_obj);

    PyRun_SimpleString("import pyDes");
    PyRun_SimpleString("decrypter = pyDes.des(key, pyDes.ECB, b\"\\0\\0\\0\\0\\0\\0\\0\\0\", pad=None, padmode=pyDes.PAD_PKCS5)");

    PyObject *ciphertext_obj = PyBytes_FromStringAndSize(kCiphertext.content(), kCiphertext.size());
    PyDict_SetItemString(main_dict, "ciphertext", ciphertext_obj);
    PyRun_SimpleString("plaintext = decrypter.decrypt(ciphertext)");

    PyObject *plaintext_obj = PyMapping_GetItemString(main_dict, "plaintext");

    char *pt = NULL;
    Py_ssize_t pt_len = 0;
    int ret = PyBytes_AsStringAndSize(plaintext_obj, &pt, &pt_len);
    ret_plaintext.Append(pt_len, pt);
    return;
}

void PythonFunction::LZString_decompresFromBase64(const std::string &kSrc, std::string &ret_result)
{
    PyObject *pModule = NULL, *pDict = NULL, *pClass = NULL, *pInstance = NULL, *result = NULL;
    pModule = PyImport_ImportModule("lzstring"); //引入模块
    if (!pModule) {
        PyErr_Print();
        return;
    }
    pDict = PyModule_GetDict(pModule); //获取模块字典属性
    pClass = PyDict_GetItemString(pDict, "LZString"); //通过字典属性获取模块中的类
    pInstance = PyObject_CallObject(pClass, NULL);//实例化获取的类
    result = PyObject_CallMethod(pInstance, "decompressFromBase64", "(s)", kSrc.c_str()); //调用类的方法
    if (!result) {
        PyErr_Print();
    }
    char* plain_string = NULL;
    PyArg_Parse(result, "s", &plain_string); //将python类型的返回值转换为c/c++类型
    ret_result.assign(plain_string);
    return;
}
