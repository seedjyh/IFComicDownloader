//
//   File name      : SystemTime.h
//
//   Code by        : jiangyonghang
//
//   Project name   : FindNoServerLite
//
//   Create datetime: 2010-10-22 10:54:39
//

#ifndef _FINDNOSERVERLITE_SYSTEMTIME_H_
#define _FINDNOSERVERLITE_SYSTEMTIME_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <string>

// Headers from other projects
#include "IFMacros/DevelopMacros.h"

// Headers of current project
// ...

#define SYSTEMTIME_WEEKDAY_CHANGE(x) ((0 == x)?(7):(x))

class SystemTime
{
    unsigned int year_;
    unsigned int month_;
    unsigned int day_;

    unsigned int hour_;
    unsigned int minute_;
    unsigned int second_;

    unsigned int microsecond_;

    unsigned int day_of_week_;

public:
    SystemTime();
    ~SystemTime(){};

    // 时间限制在1970-1-1以后，3000-1-1之前，数字限制见下。
    int Init(
        unsigned int year,
        unsigned int month,
        unsigned int day,
        unsigned int hour,
        unsigned int minute,
        unsigned int second,
        unsigned int microsecond,
        unsigned int day_of_week
    );

    unsigned int year()        const {return year_;}        // from AD
    unsigned int month()       const {return month_;}       // 1 - 12
    unsigned int day()         const {return day_;}         // 1 - 31
    unsigned int hour()        const {return hour_;}        // 0 - 23
    unsigned int minute()      const {return minute_;}      // 0 - 59
    unsigned int second()      const {return second_;}      // 0 - 59
    unsigned int microsecond() const {return microsecond_;} // 0 - 999,999
    unsigned int day_of_week() const {return day_of_week_;} // 1 - 7

    // 返回正整数。从1970-1-1开始的微秒数。返回0表示出错。
    unsigned __int64 GetMicroSecond() const;

    // 检查日期是否符合要求（月和日要符合闰年标准）。
    static int IsValidDate(unsigned int year, unsigned int month, unsigned int day);

    static int IsLeapYear(unsigned int year);

    // 转换成YYYY-MM-DD hh:mm:ss.xxx的格式的字符串。
    const std::string toString() const;

protected:
private:
    DISALLOW_COPY_AND_ASSIGN(SystemTime);
};

#endif
