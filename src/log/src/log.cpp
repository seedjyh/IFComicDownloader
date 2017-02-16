//
//   File name      : log.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-15 00:06:10
//

// Inherited header
#include "../include/log.h"

// C system headers
#include <stdarg.h>
#include <assert.h>

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "Logger.h"

static Logger s_logger;

// 函数功能见声明部分。
void log_init(const char kRootPath[], eLogLevel lowest_level)
{
    assert(kRootPath);
    s_logger.set_root_path(std::string(kRootPath));
    s_logger.set_lowest_level(lowest_level);
    return;
}

// 函数功能见声明部分。
void log_debug(const LOG_HANDLE *kHandle, const char kFormat[], ...)
{
    va_list ap;
    va_start(ap, kFormat);
    s_logger.log(kHandle, eLogLevel_Debug, kFormat, ap);
    va_end(ap);
    return;
}

// 函数功能见声明部分。
void log_info(const LOG_HANDLE *kHandle, const char kFormat[], ...)
{
    va_list ap;
    va_start(ap, kFormat);
    s_logger.log(kHandle, eLogLevel_Info, kFormat, ap);
    va_end(ap);
    return;
}

// 函数功能见声明部分。
void log_warning(const LOG_HANDLE *kHandle, const char kFormat[], ...)
{
    va_list ap;
    va_start(ap, kFormat);
    s_logger.log(kHandle, eLogLevel_Warning, kFormat, ap);
    va_end(ap);
    return;
}

// 函数功能见声明部分。
void log_error(const LOG_HANDLE *kHandle, const char kFormat[], ...)
{
    va_list ap;
    va_start(ap, kFormat);
    s_logger.log(kHandle, eLogLevel_Error, kFormat, ap);
    va_end(ap);
    return;
}

// 函数功能见声明部分。
void log_critical(const LOG_HANDLE *kHandle, const char kFormat[], ...)
{
    va_list ap;
    va_start(ap, kFormat);
    s_logger.log(kHandle, eLogLevel_Critical, kFormat, ap);
    va_end(ap);
    return;
}

