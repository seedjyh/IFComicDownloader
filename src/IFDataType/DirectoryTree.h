//
//   File name      : DirectoryTree.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2012-06-22 15:17:52
//

#ifndef _IFDATATYPE_SRC_DIRECTORYTREE_H_
#define _IFDATATYPE_SRC_DIRECTORYTREE_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <vector>

// Headers from other projects
// ...

// Headers of current project
#include "Tstring.h"

class FileHolder;

class DirectoryTree
{
	Tstring name_;
	std::vector<DirectoryTree*> child_directory_list_;
	std::vector<FileHolder*> child_file_list_;
public:
	DirectoryTree(const Tstring &kName):name_(kName){child_directory_list_.clear(); child_file_list_.clear();}
	~DirectoryTree();

	const Tstring& name() const {return name_;}

	int GetChildDirectoryCount() const {return child_directory_list_.size();}

	int GetChildFileCount() const {return child_file_list_.size();}

	const DirectoryTree* GetChildDirectory(int index) const
	{
		if (index < 0)
		{
			return NULL;
		}

		if (index >= (int)child_directory_list_.size() )
		{
			return NULL;
		}

		return child_directory_list_[index];
	}

    const DirectoryTree* GetChildDirectory(const Tstring &kDirName) const
    {
        for (int i = 0; i < static_cast<int>(child_directory_list_.size() ); i++)
        {
            if (child_directory_list_[i]->name() == kDirName)
            {
                return child_directory_list_[i];
            }
        }
        return NULL;
    }

	const FileHolder* GetChildFile(int index) const
	{
		if (index < 0)
		{
			return NULL;
		}

		if (index >= (int)child_file_list_.size() )
		{
			return NULL;
		}

		return child_file_list_[index];
	}

	void AppendChildDirectory(DirectoryTree *new_directory);

	void AppendChildFile(FileHolder *new_file);

protected:
private:
};

#endif
