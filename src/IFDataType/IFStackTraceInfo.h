//
//   File name      : IFStackTraceInfo.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2012-06-04 23:33:4
//

#ifndef _IFDATATYPE_SRC_IFSTACKTRACEINFO_H_
#define _IFDATATYPE_SRC_IFSTACKTRACEINFO_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <string>

// Headers from other projects
// ...

// Headers of current project
// ...

#define NEW_STACK_TRACE_INFO_OBJECT IFStackTraceInfo(__FUNCTION__, __FILE__, __LINE__)

class IFStackTraceInfo
{
	std::string function_name_;
	std::string file_name_;
	int			line_number_;
public:
	IFStackTraceInfo(const char kFunctionName[], const char kFileName[], int line_number)
    :	function_name_(kFunctionName),
        file_name_(kFileName),
        line_number_(line_number){};
	~IFStackTraceInfo(){};

    const std::string& function_name() const {return function_name_;}
    const std::string& file_name() const {return file_name_;}
    int line_number() const {return line_number_;}
protected:
private:
};

#endif
