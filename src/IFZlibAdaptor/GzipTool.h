//
//   File name      : GzipTool.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFZlibAdaptor
//
//   Create datetime: 2012-10-04 14:13:16
//

#ifndef _IFZLIBADAPTOR_GZIPTOOL_H_
#define _IFZLIBADAPTOR_GZIPTOOL_H_ 1

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

class DataHolder;

class GzipTool
{
public:
    static int Unzip(int source_len, const char kSource[], DataHolder &ret_result);
protected:
private:
    GzipTool(){};
    ~GzipTool(){};
};

#endif
