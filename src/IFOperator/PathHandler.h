//
//   File name      : PathHandler.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFOperator
//
//   Create datetime: 2012-04-04 21:27:4
//

#ifndef _IFCOMICDOWNLOADER_IFOPERATOR_PATHHANDLER_H_
#define _IFCOMICDOWNLOADER_IFOPERATOR_PATHHANDLER_H_ 1

// Tested or implemented header
// ...

// C system headers
#include <windows.h>

// C++ system headers
#include <string>
#include <vector>

// Headers from other projects
#include "IFDataType/PathTypes.h"

// Headers of current project
// ...

class PathHandler
{
public:
    static int Remove(const TCHAR kPath[]);
	static int Remove(const Tstring &kPath) {return Remove(kPath.c_str() );}
    static int List(const Tstring &kRootPath, PathList &ret_file_list, PathList &ret_directory_list);
    static int CreatePathRecursive(const Tstring &kPath);

    static void Validate(std::string &path);
    static int IsValidate(const Tstring &kPath);
	static void Validate(Tstring &path);
    static int CreatePath(const Tstring &kPath);
    static void GetSearchModal(const TCHAR kRootPath[], TCHAR ret_search_modal[]);

    static void TransSlashToBackslash(Tstring &kPath);
    static bool CheckFileExistance(const Tstring &kFilePath);
protected:
private:
    PathHandler(){};
    ~PathHandler(){};
};

#endif