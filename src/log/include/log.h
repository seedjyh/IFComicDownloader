//
//   File name      : log.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-14 22:20:05
//

#ifndef _LOG_LOG_H_
#define _LOG_LOG_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "enum_def.h"
#include "log_handle.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // 日志打印模块初始化。
    // [in] kRootPath 日志存放的根路径。
    // [in] lowest_level 打印日志的严重度下限。严重度达到或超过这个下限的日志需要打印。
    void log_init(const char kRootPath[], eLogLevel lowest_level);

    // 打印 debug 严重度的日志。
    void log_debug(const LOG_HANDLE *kHandle, const char kFormat[], ...);

    // 打印 info 严重度的日志。
    void log_info(const LOG_HANDLE *kHandle, const char kFormat[], ...);

    // 打印 warning 严重度的日志。
    void log_warning(const LOG_HANDLE *kHandle, const char kFormat[], ...);

    // 打印 error 严重度的日志。
    void log_error(const LOG_HANDLE *kHandle, const char kFormat[], ...);

    // 打印 critical 严重度的日志。
    void log_critical(const LOG_HANDLE *kHandle, const char kFormat[], ...);


#ifdef __cplusplus
}
#endif

#endif
