//
//   File name      : ZipTool.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFZlibAdaptor
//
//   Create datetime: 2013-01-05 21:20:24
//

#ifndef _IFZLIBADAPTOR_ZIPTOOL_H_
#define _IFZLIBADAPTOR_ZIPTOOL_H_ 1

// Tested or implemented header
// ...

// C system headers
#include <stdio.h>

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class Tstring;

class ZipTool
{
public:
    static int Unzip(const Tstring &kZipFilePathName, const Tstring &kUnzipTargetPath);

    // ��fin��ȡ����Ϊin_length�����ݣ���ѹ����д��fout��fout��Ҫclose��
    static int UnzipF2F(FILE *fin, int all_in_length, FILE *fout);

    static int JumpFileHeader(FILE *fin);

    // ��fin��ȡ����Ϊin_length�����ݣ�ֱ��д��fout��fout��Ҫclose��
    static int CopyF2F(FILE *fin, int all_in_length, FILE *fout);
protected:
private:
    ZipTool(){};
    ~ZipTool(){};
};

#endif
