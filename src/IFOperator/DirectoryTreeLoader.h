//
//   File name      : DirectoryTreeLoader.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFOperator
//
//   Create datetime: 2012-06-22 15:30:12
//

#ifndef _IFOPERATOR_SRC_DIRECTORYTREELOADER_H_
#define _IFOPERATOR_SRC_DIRECTORYTREELOADER_H_ 1

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

class Tstring;
class DirectoryTree;
class FileHolder;

typedef unsigned long long FileSize;

class DirectoryTreeLoader
{
public:
	static DirectoryTree* Load(const Tstring &kRootPath);

    static FileHolder* ReadFile(const Tstring &kFilePathName);

	static void Format(const Tstring &kPath, Tstring &ret_path);

	static void GetName(const Tstring &kPathName, Tstring &ret_name);

	// 如果文件不存在则抛异常IFExceptionFileNotExist
	static FileSize GetFileSize(const Tstring &kFilePathName);

protected:
private:
	DirectoryTreeLoader(){};
	~DirectoryTreeLoader(){};
};

#endif
