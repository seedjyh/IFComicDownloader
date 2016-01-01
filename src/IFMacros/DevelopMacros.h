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

// 禁止使用拷贝构造函数和 operator= 赋值操作的宏
// 应该类的 private: 中使用
// From google C++ Style

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)

#endif
