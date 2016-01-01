//
//   File name      : IFExceptionFileNotExist.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFOperator
//
//   Create datetime: 2012-06-22 12:16:26
//

#ifndef _IFOPERATOR_SRC_IFEXCEPTIONFILENOTEXIST_H_
#define _IFOPERATOR_SRC_IFEXCEPTIONFILENOTEXIST_H_ 1

// Tested or implemented header
#include "IFDataType/IFException.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "IFOperator/CodeTransformer.h"

class IFExceptionFileNotExist: public IFException
{
public:
	IFExceptionFileNotExist(const Tstring &kFilePath)
    :   IFException(CodeTransformer::TransTstringToString(kFilePath)){
    };
	virtual ~IFExceptionFileNotExist(){};
protected:
private:
};

#endif
