//
//   File name      : DateTime.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : RIG_VSBS
//
//   Create datetime: 2017-02-16 11:04:54
//

// Implemented header
#include "../include/DateTime.h"

// C system headers
#include <time.h>
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

DateTime::DateTime()
:   year_(0),
    month_(0),
    day_(0),
    hour_(0),
    minute_(0),
    second_(0),
    micro_second_(0){}

std::string DateTime::toDateString() const
{
    char buf[128] = "";
    sprintf(buf, "%04d-%02d-%02d",
        year_, month_, day_);
    return std::string(buf);
}

std::string DateTime::toDateTimeString() const
{
    char buf[128] = "";
    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d.%06d",
        year_, month_, day_,
        hour_, minute_, second_,
        micro_second_);
    return std::string(buf);
}

void DateTime::setNow(DateTime &ret)
{
#ifdef WIN32
    SYSTEMTIME now_time;
    GetLocalTime(&now_time);
    ret.year_ = now_time.wYear;
    ret.month_ = now_time.wMonth;
    ret.day_ = now_time.wDay;
    ret.hour_ = now_time.wHour;
    ret.minute_ = now_time.wMinute;
    ret.second_ = now_time.wSecond;
    ret.micro_second_ = now_time.wMilliseconds * 1000; // Windows只能精确到毫秒。
#else // linux
    timeval now;
    gettimeofday(&now, NULL);
    struct tm *ptm_ = localtime(&now);
    ret.year_ = ptm->tm_year;
    ret.month_ = ptm->tm_mon;
    ret.day_ = ptm->tm_mday;
    ret.hour_ = ptm->tm_hour;
    ret.minute_ = ptm->tm_min;
    ret.second_ = ptm->tm_sec;
    ret.micro_second_ = now.tv_usec;
#endif
    return;
}
