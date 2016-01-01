//
//   File name      : IFThrowable.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFDataType
//
//   Create datetime: 2012-06-04 23:26:04
//

#ifndef _IFDATATYPE_SRC_IFTHROWABLE_H_
#define _IFDATATYPE_SRC_IFTHROWABLE_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <vector>
#include <ostream>

// Headers from other projects
// ...

// Headers of current project
#include "IFStackTraceInfo.h"

class IFThrowable
{
    std::vector<IFStackTraceInfo> stack_trace_info_list_;
public:
    IFThrowable(){}
	virtual ~IFThrowable(){};

    void ToString(std::string &ret_result) const;

    void PrintStackTrace(std::ostream &output) const;

    void AppendStackTraceInfo(const IFStackTraceInfo &kNewInfo);

protected:
private:
};

#endif
