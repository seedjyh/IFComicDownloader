//
//   File name      : DateTime.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : RIG_VSBS
//
//   Create datetime: 2017-02-16 11:03:47
//

#ifndef _DATETIME_H_
#define _DATETIME_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
#include <string>

// Headers from other projects
// ...

// Headers of current project
// ...

class DateTime
{
    int year_;
    int month_;
    int day_;
    int hour_;
    int minute_;
    int second_;
    int micro_second_;
public:
    DateTime();
    ~DateTime(){}
    std::string toDateString() const;
    std::string toDateTimeString() const;
    static void setNow(DateTime &ret);
protected:
private:
};

#endif
