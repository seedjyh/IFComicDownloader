//
//   File name      : Logger.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-15 00:28:48
//

// Inherited header
#include "Logger.h"

// C system headers
#include <stdio.h>
#include <assert.h>

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "../include/log_handle.h"
#include "../../IFMacros/BasicOperateMacro.h"
#include "../../os_api/include/DateTime.h"
#include "../../os_api/include/FileOperator.h"
#include "../../os_api/include/functions.h"

void Logger::log(const LOG_HANDLE *kHandle, eLogLevel level, const char kFormat[], va_list ap)
{
    if (level < lowest_level_)
    {
        return;
    }

    std::string file_uri = generateTargetFileUri();
    FILE *fp = fopen(file_uri.c_str(), "ab");
    if (NULL == fp)
    {
        fprintf(stderr, "Error! log system error, can not open log file to write in. File URI: %s\n", file_uri.c_str());
        return;
    }

    appendDatatime(fp);
    fputc('|', fp);
    appendLevel(fp, level);
    fputc('|', fp);
    appendHandleData(fp, kHandle);
    fputc('|', fp);
    vfprintf(fp, kFormat, ap);
    fputc('\n', fp);
    MY_FCLOSE(fp);

    if (isLogFileTooLarge(file_uri))
    {
        renameLogFile(file_uri);
    }
    return;
}

std::string Logger::generateTargetFileUri()
{
    DateTime now;
    DateTime::setNow(now);
    char file_uri_buf[256] = "";
    SNPRINTF(file_uri_buf, sizeof(file_uri_buf), "%sifcd_%s.log", root_path_.c_str(), now.toDateString().c_str());
    MY_SET_TAIL_NULL(file_uri_buf);
    return std::string(file_uri_buf);
}

void Logger::appendDatatime(FILE *fp)
{
    DateTime now;
    DateTime::setNow(now);
    fputs(now.toDateTimeString().c_str(), fp);
    return;
}

void Logger::appendLevel(FILE *fp, eLogLevel level)
{
    fputs(getLevelName(level), fp);
    return;
}

void Logger::appendHandleData(FILE *fp, const LOG_HANDLE *kHandle)
{
    char buffer[256] = "";
    log_handle_serialize_data(sizeof(buffer), buffer, kHandle);
    fputs(buffer, fp);
    return;
}

bool Logger::isLogFileTooLarge(const std::string &kFileUri)
{
    const static long s_kMaxLogFileSize = 1 << 30;
    FILE *fp = fopen(kFileUri.c_str(), "rb");
    if (NULL == fp)
    {
        return false;
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    MY_FCLOSE(fp);
    return file_size >= s_kMaxLogFileSize;
}

void Logger::renameLogFile(const std::string &kFileUri)
{
    FileOperator::rename(kFileUri, getNewFileUriForRenaming(kFileUri));
    return;
}

const char* Logger::getLevelName(eLogLevel level)
{
    switch (level)
    {
    case eLogLevel_Debug:
        return "DEBUG";
        break;
    case eLogLevel_Info:
        return "INFO";
        break;
    case eLogLevel_Warning:
        return "WARNING";
        break;
    case eLogLevel_Error:
        return "ERROR";
        break;
    case eLogLevel_Critical:
        return "CRITICAL";
        break;
    default:
        return "(unknown)";
        break;
    }
}

std::string Logger::getNewFileUriForRenaming(const std::string &kFileUri)
{
    DateTime now;
    DateTime::setNow(now);
    std::string now_str = now.toDateTimeString();
    for (std::string::iterator ite = now_str.begin(); ite != now_str.end(); ++ite)
    {
        if (':' == *ite)
        {
            *ite = '.';
        }
    }
    return kFileUri + "(" + now_str + ")";
}

