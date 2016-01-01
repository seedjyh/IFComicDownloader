//
//   File name      : DirectoryTree.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2012-06-22 15:24:42
//

// Tested or implemented header
#include "DirectoryTree.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFMacros/BasicOperateMacro.h"

// Headers of current project
#include "FileHolder.h"

DirectoryTree::~DirectoryTree()
{
	for (int i = 0; i < (int)child_directory_list_.size(); i++)
	{
		MY_DELETE(child_directory_list_[i]);
	}
	child_directory_list_.clear();

	for (int i = 0; i < (int)child_file_list_.size(); i++)
	{
		MY_DELETE(child_file_list_[i]);
	}
	child_file_list_.clear();
}

void DirectoryTree::AppendChildDirectory(DirectoryTree *new_directory)
{
	child_directory_list_.push_back(new_directory);
	return;
}

void DirectoryTree::AppendChildFile(FileHolder *new_file)
{
	child_file_list_.push_back(new_file);
	return;
}
