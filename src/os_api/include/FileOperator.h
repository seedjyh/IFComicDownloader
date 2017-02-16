//
//   File name      : FileOperator.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : RIG_VSBS
//
//   Create datetime: 2017-02-16 12:21:38
//

#ifndef _FILEOPERATOR_H_
#define _FILEOPERATOR_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
#include <string>

// Headers from other projects
// ...

// Headers of current project
// ...

class FileOperator
{
public:
    // 将硬盘上的文件重命名。
    // 参数：
    // - kOldUri [ in ] 原文件URI。
    // - kNewUri [ in ] 新文件URI。
    // 返回值：
    // - 成功返回true，失败返回false。
    static bool rename(const std::string &kOldUri, const std::string &kNewUri);
protected:
private:
    FileOperator(){}
    ~FileOperator(){}
};

#endif
