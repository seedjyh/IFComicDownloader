//
//   File name      : SystemTime.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : FindNoServerLite
//
//   Create datetime: 2010-10-22 13:55:47
//

// Tested or implemented header
#include "SystemTime.h"

// C system headers
#include <assert.h>

#if defined WIN32
#include <windows.h>
#elif defined linux
#include <sys/time.h>
#include <time.h>
#endif


// C++ system headers
#include <string>

// Headers from other projects
#include "IFMacros/BasicMacro.h"

// Headers of current project
// ...

SystemTime::SystemTime()
:   year_(1970),
    month_(1),
    day_(1),
    hour_(0),
    minute_(0),
    second_(0),
    day_of_week_(4){
};

int SystemTime::Init(
    unsigned int year,
    unsigned int month,
    unsigned int day,
    unsigned int hour,
    unsigned int minute,
    unsigned int second,
    unsigned int microsecond,
    unsigned int day_of_week
)
{
    int nResult  = false;
    int nRetCode = false;

    MY_PROCESS_ERROR(IsValidDate(year, month, day) );
    MY_PROCESS_ERROR(hour <= 23);
    MY_PROCESS_ERROR(minute <= 59);
    MY_PROCESS_ERROR(second <= 59);
    MY_PROCESS_ERROR(microsecond < 1e6);
    MY_PROCESS_ERROR(day_of_week > 0);

    year_        = year;
    month_       = month;
    day_         = day;
    hour_        = hour;
    minute_      = minute;
    second_      = second;
    microsecond_ = microsecond;
    day_of_week_ = day_of_week;

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

unsigned __int64 SystemTime::GetMicroSecond() const
{
    unsigned __int64 result      = 0;
    unsigned __int64 work_result = 0;

#if defined WIN32
    FILETIME   file_time_win32;
    SYSTEMTIME time_win32;

    unsigned __int64 microsecond_to_now  = 0;
    unsigned __int64 microsecond_to_1970 = 0;

    time_win32.wYear         = year_;
    time_win32.wMonth        = month_;
    time_win32.wDay          = day_;
    time_win32.wHour         = hour_;
    time_win32.wMinute       = minute_;
    time_win32.wSecond       = second_;
    time_win32.wMilliseconds = microsecond_ / 1000;

    MY_PROCESS_ERROR(SystemTimeToFileTime(&time_win32, &file_time_win32) );

    microsecond_to_now  = file_time_win32.dwHighDateTime;
    microsecond_to_now <<= 32;
    microsecond_to_now |= file_time_win32.dwLowDateTime;

    time_win32.wYear         = 1970;
    time_win32.wMonth        = 1;
    time_win32.wDay          = 1;
    time_win32.wHour         = 0;
    time_win32.wMinute       = 0;
    time_win32.wSecond       = 0;
    time_win32.wMilliseconds = 0;

    MY_PROCESS_ERROR(SystemTimeToFileTime(&time_win32, &file_time_win32) );

    microsecond_to_1970  = file_time_win32.dwHighDateTime;
    microsecond_to_1970 <<= 32;
    microsecond_to_1970 |= file_time_win32.dwLowDateTime;

    MY_PROCESS_ERROR(microsecond_to_now >= microsecond_to_1970);
    work_result = microsecond_to_now - microsecond_to_1970;

#elif defined linux
    struct tm target_time;
    time_t second_count = 0;

    unsigned __int64 microsecond_from_1900 = 0;
    const static unsigned __int64 kDayFrom1900To1970 = 365 * 70 + 17;

    target_time.tm_year = year_ - 1900;
    target_time.tm_mon  = month_;
    target_time.tm_mday = day_;
    target_time.tm_hour = hour_;
    target_time.tm_min  = minute_;
    target_time.tm_sec  = second_;

    microsecond_from_1900 = mktime(&target_time);
    MY_PROCESS_ERROR(second_count != -1);

    work_result  = microsecond_from_1900 - kDayFrom1900To1970 * 86400;
    work_result *= 1000000;
    work_result += microsecond_;

#endif


// Exit1:
    result = work_result;
Exit0:
    return result;
}

int SystemTime::IsValidDate(unsigned int year, unsigned int month, unsigned int day)
{
    int nResult  = false;
    int nRetCode = false;

    static unsigned int day_of_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    unsigned int expected_max_day_of_month = 0;

    MY_PROCESS_ERROR(year >= 1);
    MY_PROCESS_ERROR( (month >= 1) || (month <= 12) );
    MY_PROCESS_ERROR(day >= 1);

    expected_max_day_of_month = day_of_month[month];

    if (
        (2 == month) &&
        (IsLeapYear(year) )
    )
    {
        expected_max_day_of_month++;
    }

    MY_PROCESS_ERROR(day <= expected_max_day_of_month);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int SystemTime::IsLeapYear(unsigned int year)
{
    int nResult  = false;
    int nRetCode = false;

    MY_PROCESS_ERROR(0 == year % 4);

    if (year % 400 != 0)
    {
        MY_PROCESS_ERROR(year % 40);
    }

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

const std::string SystemTime::toString() const
{
    char buffer[128] = { '\0' };
    _snprintf(buffer, MY_SIZE_OF_ARRAY(buffer),
        "%04d-%02d-%02d %02d:%02d:%02d.%03d",
        year_, month_, day_, hour_, minute_, second_, microsecond_ / 1000
        );
    MY_SET_TAIL_NULL(buffer);
    return std::string(buffer);
}
