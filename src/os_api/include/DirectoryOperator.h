//
//   File name      : DirectoryOperator.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : RIG_VSBS
//
//   Create datetime: 2017-02-16 10:12:08
//

#ifndef _DIRECTORYOPERATOR_H_
#define _DIRECTORYOPERATOR_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
#include <list>
#include <string>

// Headers from other projects
// ...

// Headers of current project
// ...

class DirectoryOperator
{
public:
    // 删除一个目录（无论是不是空的）。
    static bool deleteDirectory(const std::string &kPath);
    // 创建一个目录（如果没有父目录则递归创建）。
    static bool createDirectory(const std::string &kPath);
    // 获取一个目录下的文件列表（不含子目录）。
    static std::list<std::string> getFilesInDirectory(const std::string &kRootPath);
protected:
private:
    DirectoryOperator(){}
    ~DirectoryOperator(){}
};

#endif
