//
//   File name      : Testlog.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-15 00:30:23
//

#ifdef _GTEST_

// Tested header
#include "../include/log.h"

// C system headers
#include <assert.h>

// C++ system headers
#include <string>
#include <vector>

// Headers from other projects
#include <gtest/gtest.h>

// Headers of current project
#include "../../os_api/include/DirectoryOperator.h"
#include "../../IFMacros/BasicOperateMacro.h"

void prepareDirectoryForTest(const std::string &kPath)
{
    assert(DirectoryOperator::deleteDirectory(kPath));
    assert(DirectoryOperator::createDirectory(kPath));
    assert(0 == DirectoryOperator::getFilesInDirectory(kPath).size());
    return;
}

void cleanupDirectoryForTest(const std::string &kPath)
{
    assert(DirectoryOperator::deleteDirectory(kPath));
    return;
}

static std::vector<std::string> getFileLine(const std::string &kFileUrl)
{
    std::vector<std::string> line_list;
    std::string now_line;
    FILE *fp = fopen(kFileUrl.c_str(), "rb");
    while (1)
    {
        char ch = fgetc(fp);
        if ('\n' == ch)
        {
            line_list.push_back(now_line);
            now_line.clear();
        }
        else if (EOF == ch)
        {
            line_list.push_back(now_line);
            break;
        }
        else
        {
            now_line += ch;
        }
    }
    MY_FCLOSE(fp);
    return line_list;
}

static void checkLogLine(const char kExpectedLogLine[], const std::string &kLine)
{
    size_t time_part_len = strlen("YYYY-MM-DD hh:mm:ss.uuuuuu");
    ASSERT_GT(kLine.size(), time_part_len);
    ASSERT_STREQ(kExpectedLogLine + time_part_len, kLine.c_str() + time_part_len);
    return;
}

TEST(log, level_test)
{
    const std::string log_root_path("temp_for_test/");
    prepareDirectoryForTest(log_root_path);

    LOG_HANDLE handle;
    log_handle_init(&handle);
    log_handle_set_string(&handle, "ptype", "P");
    log_handle_set_int(&handle, "pid", 3);
    log_handle_set_uint64(&handle, "usid", 1LL<<63);

    // do log
    log_init(log_root_path.c_str(), eLogLevel_Info);
    log_debug(&handle, "This is DEBUG: %s", "hello, debug");
    log_info(&handle, "This is INFO: %s", "hello, info");
    log_warning(&handle, "This is WARNING: %s", "hello, warning");
    log_error(&handle, "This is ERROR: %s", "hello, error");
    log_critical(&handle, "This is CRITICAL: %s", "hello, critical");

    std::list<std::string> file_list = DirectoryOperator::getFilesInDirectory(log_root_path);
    ASSERT_EQ(1, file_list.size());// 从打印的量看，应该有且仅有一个日志文件。
    std::string log_file_name = (*file_list.begin());
    std::vector<std::string> line_list = getFileLine(log_file_name);
    ASSERT_EQ(5, line_list.size()); // 最后一行是空行。
    checkLogLine("2017-02-15 00:00:00.000000|INFO|ptype=P,pid=3,usid=9223372036854775808|This is INFO: hello, info", line_list[0]);
    checkLogLine("2017-02-15 00:00:00.000000|WARNING|ptype=P,pid=3,usid=9223372036854775808|This is WARNING: hello, warning", line_list[1]);
    checkLogLine("2017-02-15 00:00:00.000000|ERROR|ptype=P,pid=3,usid=9223372036854775808|This is ERROR: hello, error", line_list[2]);
    checkLogLine("2017-02-15 00:00:00.000000|CRITICAL|ptype=P,pid=3,usid=9223372036854775808|This is CRITICAL: hello, critical", line_list[3]);
    cleanupDirectoryForTest(log_root_path);
}

#endif
