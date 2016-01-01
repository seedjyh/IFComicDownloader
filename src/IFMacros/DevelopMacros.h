//
//   File name      : DevelopMacros.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFMacros
//
//   Create datetime: 2011-03-30 09:52:48
//

#ifndef _IFMACROS_DEVELOPMACROS_H_
#define _IFMACROS_DEVELOPMACROS_H_ 1

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

// ��ֹʹ�ÿ������캯���� operator= ��ֵ�����ĺ�
// Ӧ����� private: ��ʹ��
// From google C++ Style

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)

#endif
