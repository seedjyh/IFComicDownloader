//
//   File name      : NumberOperator.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFOperator
//
//   Create datetime: 2011-03-31 12:30:50
//

#ifndef _IFOPERATOR_NUMBEROPERATOR_H_
#define _IFOPERATOR_NUMBEROPERATOR_H_ 1

// Tested or implemented header
// ...

// C system headers
#include <tchar.h>

// C++ system headers
#include <string>
using namespace std;

// Headers from other projects
// ...

// Headers of current project
// ...

class Tstring;

class NumberOperator
{
public:
    static int ItoA(int num, const char kFormat[], string &strnum);
    static int ItoA(int num, const Tstring &kFormat, Tstring &strnum);
    static Tstring ItoA(int num, const Tstring &kFormat);

    static int DtoA(double num, const char kFormat[], string &strnum);
    static int DtoA(double num, const Tstring &kFormat, Tstring &strnum);
protected:
private:
    NumberOperator(){};
    ~NumberOperator(){};
};

#endif
