//
//   File name      : DirectoryTreeLoader.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFOperator
//
//   Create datetime: 2012-06-22 15:48:18
//

// Tested or implemented header
#include "DirectoryTreeLoader.h"

// C system headers
#include <assert.h>

// C++ system headers
// ...

// Headers from other projects
#include "IFDataType/DirectoryTree.h"
#include "IFDataType/FileHolder.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFMacros/BasicProcessMacro.h"
#include "IFDataType/Tstring.h"
#include "IFDataType/PathTypes.h"
#include "IFOperator/PathHandler.h"
#include "IFOperator/IFExceptionFileNotExist.h"

// Headers of current project
// ...

DirectoryTree* DirectoryTreeLoader::Load(const Tstring &kRootPath)
{
    DirectoryTree *result      = NULL;
    DirectoryTree *work_result = NULL;

    int nRetCode = false;

	Tstring root_path;
	Tstring root_name;

	Format(kRootPath, root_path);
	GetName(root_path, root_name);

    work_result = new DirectoryTree(root_name);

	PathList file_list;
	PathList path_list;

	MY_PROCESS_ERROR(PathHandler::List(root_path, file_list, path_list) );

    for (int i = 0; i < static_cast<int>(path_list.size()); i++)
	{
		work_result->AppendChildDirectory(Load(path_list[i]) );
	}

    for (int i = 0; i < static_cast<int>(file_list.size()); i++)
	{
		Tstring file_path_name;
		Tstring file_name;
		int file_size = 0;

		Format(file_list[i], file_path_name);
		GetName(file_path_name, file_name);

        work_result->AppendChildFile(ReadFile(file_list[i]));
	}

// Exit1:
    result 	    = work_result;
    work_result = NULL;
Exit0:
    MY_DELETE(work_result);
    return result;
}

FileHolder* DirectoryTreeLoader::ReadFile(const Tstring &kFilePathName)
{
	FILE *fp = _tfopen(kFilePathName.c_str(), TEXT("rb") );

    int file_size = static_cast<int>(GetFileSize(kFilePathName));

	char *buffer = new char[file_size];

	int read_count = fread(buffer, 1, file_size, fp);

	assert(file_size == read_count);

	MY_FCLOSE(fp);

    FileHolder *result = new FileHolder(kFilePathName, file_size, buffer);
    MY_DELETEARRAY(buffer);

    return result;
}

void DirectoryTreeLoader::Format(const Tstring &kPath, Tstring &ret_path)
{
	Tstring temp_path = kPath;
	for (int i = 0; i < temp_path.size(); i++)
	{
		if (TCHAR('/') == temp_path[i])
		{
			temp_path[i] = TCHAR('\\');
		}
	}

	ret_path = temp_path;

	return;
}

void DirectoryTreeLoader::GetName(const Tstring &kPathName, Tstring &ret_name)
{
	Tstring temp_name = kPathName;

	if (TCHAR('\\') == temp_name[temp_name.length() - 1])
	{
		temp_name.resize(temp_name.length() - 1);
	}

	int last_slash = -1;

	for (int i = temp_name.length() - 1; i >= 0; i--)
	{
		if (TCHAR('\\') == temp_name[i])
		{
			last_slash = i;
			break;
		}
	}

	ret_name.assign(temp_name.c_str() + last_slash + 1);

	return;
}


FileSize DirectoryTreeLoader::GetFileSize(const Tstring &kFilePathName)
{
	FileSize result = 0;
	HANDLE hIte = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA wfd;

	hIte = FindFirstFile(kFilePathName.c_str(), &wfd);
	if (INVALID_HANDLE_VALUE == hIte)
	{
        throw IFExceptionFileNotExist(kFilePathName);
	}

	result = wfd.nFileSizeHigh;
	result <<= 32;
	result |= wfd.nFileSizeLow;

	MY_FINDCLOSE(hIte);

	return result;
}
