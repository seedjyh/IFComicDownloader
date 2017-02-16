//
//   File name      : Logger.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-15 00:13:04
//

#ifndef _LOGGER_H_
#define _LOGGER_H_ 1

// Inherited header
// ...

// C system headers
#include <stdarg.h>

// C++ system headers
#include <string>

// Headers from other projects
// ...

// Headers of current project
#include "../include/enum_def.h"
#include "../include/log_handle.h"

class Logger
{
    eLogLevel lowest_level_;
    std::string root_path_;
public:
    Logger()
    :   lowest_level_(eLogLevel_Error){}
    ~Logger(){}

    void set_lowest_level(eLogLevel lowest_level) { lowest_level_ = lowest_level; }
    void set_root_path(const std::string &kRootPath) { root_path_ = kRootPath; }

    void log(const LOG_HANDLE *kHandle, eLogLevel level, const char kFormat[], va_list ap);
protected:
private:
    // 生成待写入日志的文件的文件路径。
    std::string generateTargetFileUri();

    // 在日志中写入日期、时间。
    static void appendDatatime(FILE *fp);

    // 在日志中写入日志级别。
    static void appendLevel(FILE *fp, eLogLevel level);

    // 在日志中写入日志数据信息。
    static void appendHandleData(FILE *fp, const LOG_HANDLE *kHandle);

    // 检查当前日志文件是否过大，需要重命名当前日志文件，从而在不更换写入文件的文件名的前提下换一个日志文件继续写入。
    static bool isLogFileTooLarge(const std::string &kFileUri);

    // 重命名当前日志文件URI为别的名字。
    static void renameLogFile(const std::string &kFileUri);

    // 将日志严重度级别转化为字符串（通常用于写入到日志中）。
    static const char* getLevelName(eLogLevel level);

    // 获取新的文件URI。这个新URI用于当前日志文件过大时重命名。
    static std::string getNewFileUriForRenaming(const std::string &kFileUri);
};

#endif
