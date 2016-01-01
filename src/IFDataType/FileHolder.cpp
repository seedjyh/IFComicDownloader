//
//   File name      : FileHolder.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2012-06-22 15:40:35
//

// Tested or implemented header
#include "FileHolder.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFMacros/BasicOperateMacro.h"

// Headers of current project
// ...

FileHolder::FileHolder(const Tstring &kName, int content_size, const char *kContent)
:	name_(kName),
	size_(content_size),
	content_(NULL)
{
	content_ = new char[size_];
	memcpy(content_, kContent, size_);
}

FileHolder::~FileHolder()
{
	MY_DELETEARRAY(content_);
}
