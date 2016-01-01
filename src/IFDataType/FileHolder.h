//
//   File name      : FileHolder.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2012-06-22 15:38:04
//

#ifndef _IFDATATYPE_SRC_FILEHOLDER_H_
#define _IFDATATYPE_SRC_FILEHOLDER_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "Tstring.h"

// Headers of current project
// ...

class FileHolder
{
	Tstring name_;
	int size_;
	char *content_;
public:
	FileHolder(const Tstring &kName, int content_size, const char *kContent);
	~FileHolder();

	const Tstring& name() const {return name_;}

	int size() const {return size_;}

	const char* content() const {return content_;}
protected:
private:
};

#endif
