//
//   File name      : SystemTimeFactory.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : FindNoServerLite
//
//   Create datetime: 2010-10-28 10:23:52
//

// Tested or implemented header
#include "SystemTimeFactory.h"

// C system headers
#include <stddef.h>

#if defined WIN32
#include <windows.h>
#elif defined linux
#include <sys/time.h>
#include <time.h>
#endif

// C++ system headers
// ...

// Headers from other projects
#include "IFMacros/BasicProcessMacro.h"
#include "IFMacros/BasicOperateMacro.h"

// Headers of current project
#include "SystemTime.h"

SystemTime* SystemTimeFactory::CreateLocalTime()
{
    SystemTime *result      = NULL;
    SystemTime *work_result = NULL;

    int nRetCode = false;

#if defined WIN32
    SYSTEMTIME win32_time;

    work_result = new SystemTime();
    MY_PROCESS_ERROR(work_result);

    GetLocalTime(&win32_time);

    nRetCode = work_result->Init(
        win32_time.wYear,
        win32_time.wMonth,
        win32_time.wDay,
        win32_time.wHour,
        win32_time.wMinute,
        win32_time.wSecond,
        win32_time.wMilliseconds * 1000,
        SYSTEMTIME_WEEKDAY_CHANGE(win32_time.wDayOfWeek)
    );
    MY_PROCESS_ERROR(nRetCode);

#elif defined linux
    time_t current_second_count;
    struct tm *current_time = NULL;

    struct timeval  TimeOfDay;
    struct timezone TimeZone;

    work_result = new SystemTime();
    MY_PROCESS_ERROR(work_result);

    time(&current_second_count);
    current_time = localtime(&current_second_count);

    nRetCode = gettimeofday(&TimeOfDay, &TimeZone);
    if (nRetCode)
    {
        TimeOfDay.tv_usec = 0;
    }

    nRetCode = work_result->Init(
        current_time->tm_year + 1900,
        current_time->tm_mon + 1,
        current_time->tm_mday,
        current_time->tm_hour,
        current_time->tm_min,
        current_time->tm_sec,
        TimeOfDay.tv_usec,
        current_time->tm_wday + 1
    );
    MY_PROCESS_ERROR(nRetCode);

#else
    MY_PROCESS_ERROR(false);
#endif

// Exit1:
    result 	    = work_result;
    work_result = NULL;
Exit0:
    MY_DELETE(work_result);
    return result;
}

SystemTime* SystemTimeFactory::CreateSpecificTime(
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
    SystemTime *result      = NULL;
    SystemTime *work_result = NULL;

    int nRetCode = false;

    work_result = new SystemTime;
    MY_PROCESS_ERROR(work_result);

    nRetCode = work_result->Init(
        year,
        month,
        day,
        hour,
        minute,
        second,
        microsecond,
        day_of_week
    );
    MY_PROCESS_ERROR(nRetCode);

// Exit1:
    result 	    = work_result;
    work_result = NULL;
Exit0:
    MY_DELETE(work_result);
    return result;
}

SystemTime* SystemTimeFactory::CreateFromTime(const SystemTime *kSrcTime)
{
    SystemTime *result      = NULL;
    SystemTime *work_result = NULL;

    int nRetCode = false;

    work_result = new SystemTime;
    MY_PROCESS_ERROR(work_result);

    nRetCode = work_result->Init(
        kSrcTime->year(),
        kSrcTime->month(),
        kSrcTime->day(),
        kSrcTime->hour(),
        kSrcTime->minute(),
        kSrcTime->second(),
        kSrcTime->microsecond(),
        kSrcTime->day_of_week()
    );
    MY_PROCESS_ERROR(nRetCode);

// Exit1:
    result 	    = work_result;
    work_result = NULL;
Exit0:
    MY_DELETE(work_result);
    return result;
}

SystemTime* SystemTimeFactory::CreateTimeFromOffsetSecond(unsigned int second_from_1900)
{
    SystemTime *result      = NULL;
    SystemTime *work_result = NULL;

    int nRetCode = false;

#if defined WIN32
    FILETIME file_time;
    SYSTEMTIME date_time;
    const unsigned __int64 kDayFrom1601to1900 = 365 * 300 + 74 - 7;
    unsigned __int64 nanosecond_from_1601  = 0;

    work_result = new SystemTime;
    MY_PROCESS_ERROR(work_result);

    nanosecond_from_1601 = ( (unsigned __int64)3600 * 24 * kDayFrom1601to1900 + second_from_1900) * 1000000000;
    file_time.dwLowDateTime = (unsigned int)(nanosecond_from_1601 & 0xFFFFFFFF);
    nanosecond_from_1601 >>= 32;
    file_time.dwHighDateTime = (unsigned int)(nanosecond_from_1601 & 0xFFFFFFFF);

    FileTimeToSystemTime(&file_time, &date_time);

    nRetCode = work_result->Init(
        date_time.wYear,
        date_time.wMonth,
        date_time.wDay,
        date_time.wHour,
        date_time.wMinute,
        date_time.wSecond,
        date_time.wMilliseconds * 1000,
        date_time.wDayOfWeek
    );
    MY_PROCESS_ERROR(nRetCode);

#elif defined linux
    time_t current_second_count;
    struct tm *current_time = NULL;

    struct timeval  time_of_day;
    struct timezone time_zone;

    work_result = new SystemTime;
    MY_PROCESS_ERROR(work_result);

    time(&current_second_count);
    current_time = localtime(&current_second_count);

    nRetCode = gettimeofday(&time_of_day, &time_zone);
    if (nRetCode)
    {
        time_of_day.tv_usec = 0;
    }

    nRetCode = work_result->Init(
        current_time->tm_year + 1900,
        current_time->tm_mon + 1,
        current_time->tm_mday,
        current_time->tm_hour,
        current_time->tm_min,
        current_time->tm_sec,
        time_of_day.tv_usec,
        current_time->tm_wday
    );
    MY_PROCESS_ERROR(nRetCode);

#else
    MY_PROCESS_ERROR(false);
#endif

// Exit1:
    result 	    = work_result;
    work_result = NULL;
Exit0:
    MY_DELETE(work_result);
    return result;
}
