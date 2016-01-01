//
//   File name      : IFCurlCouldNotConnectException.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFCurlAdaptor
//
//   Create datetime: 2012-06-30 09:28:27
//

#ifndef _IFCURLADAPTOR_INCLUDE_IFCURLCOULDNOTCONNECTEXCEPTION_H_
#define _IFCURLADAPTOR_INCLUDE_IFCURLCOULDNOTCONNECTEXCEPTION_H_ 1

// Tested or implemented header
#include "IFDataType/IFException.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class IFCurlCouldNotConnectException: public IFException
{
public:
	IFCurlCouldNotConnectException(){}
	virtual ~IFCurlCouldNotConnectException(){};
protected:
private:
	virtual const char* GetName() const {return "IFCurlCouldNotConnectException";}
};

#endif
