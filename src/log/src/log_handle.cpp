//
//   File name      : log_handle.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : RIG_VSBS
//
//   Create datetime: 2017-02-15 14:19:24
//

// Implemented header
#include "../include/log_handle.h"

// C system headers
#include <stdio.h>
#include <string.h>
#include <assert.h>

// C++ system headers
#include <string>
#include <sstream>

// Headers from other projects
// ...

// Headers of current project
#include "../../IFMacros/BasicOperateMacro.h"
#include "../../os_api/include/functions.h"

// LOG_HANDLE 的具体字段
typedef struct
{
    char name[8];
    char value[32];
}LOG_HANDLE_DATA;

static void setDataName(LOG_HANDLE_DATA &data, const std::string &kName)
{
    strncpy(data.name, kName.c_str(), sizeof(data.name));
    MY_SET_TAIL_NULL(data.name);
    return;
}

static void setDataValue(LOG_HANDLE_DATA &data, int value)
{
    SNPRINTF(data.value, sizeof(data.value), "%d", value);
    MY_SET_TAIL_NULL(data.value);
    return;
}

static void setDataValue(LOG_HANDLE_DATA &data, ULL value)
{
    SNPRINTF(data.value, sizeof(data.value), "%llu", value);
    MY_SET_TAIL_NULL(data.value);
    return;
}

static void setDataValue(LOG_HANDLE_DATA &data, const std::string &kValue)
{
    strncpy(data.value, kValue.c_str(), sizeof(data.value));
    MY_SET_TAIL_NULL(data.value);
    return;
}

template<typename V_T>
static void initData(LOG_HANDLE_DATA &data, const std::string &kName, V_T &kValue)
{
    memset(&data, 0, sizeof(data));
    setDataName(data, kName);
    setDataValue(data, kValue);
    return;
}

typedef struct {
    LOG_HANDLE_DATA items[4];
    size_t used_item_count;
}LOG_HANDLE_IMPL;

static bool setData(LOG_HANDLE_IMPL &impl, const LOG_HANDLE_DATA &kData)
{
    for (size_t i = 0; i < impl.used_item_count; i++)
    {
        if (0 == strcmp(impl.items[i].name, kData.name))
        {
            memcpy(&(impl.items[i]), &kData, sizeof(kData));
            return true;
        }
    }
    if (impl.used_item_count >= MY_SIZE_OF_ARRAY(impl.items))
    {
        fprintf(stderr, "ERROR in log system: %s(%d), no extra space for this data(name=\"%s\", value=\"%s\").", __FILE__, __LINE__, kData.name, kData.value);
        return false;
    }
    memcpy(&(impl.items[impl.used_item_count]), &kData, sizeof(kData));
    impl.used_item_count++;
    return true;
}

// 在编译期确保LOG_HANDLE_IMPL必定小于LOG_HANDLE。
static int test_size[(sizeof(LOG_HANDLE) >= sizeof(LOG_HANDLE_IMPL)) ? 1 : -1];

//////////////////////////////////////////////////////////////////////////

void log_handle_init(LOG_HANDLE *handle)
{
    memset(handle, 0, sizeof(LOG_HANDLE));
    return;
}

void log_handle_set_int(LOG_HANDLE *handle, const char kName[], int value)
{
    assert(handle != NULL);
    assert(kName != NULL);
    LOG_HANDLE_DATA new_data;
    initData<int>(new_data, std::string(kName), value);
    setData(*(LOG_HANDLE_IMPL*)handle, new_data);
    return;
}

void log_handle_set_uint64(LOG_HANDLE *handle, const char kName[], ULL value)
{
    assert(handle != NULL);
    assert(kName != NULL);
    LOG_HANDLE_DATA new_data;
    initData<ULL>(new_data, std::string(kName), value);
    setData(*(LOG_HANDLE_IMPL*)handle, new_data);
    return;
}

void log_handle_set_string(LOG_HANDLE *handle, const char kName[], const char kValue[])
{
    assert(handle != NULL);
    assert(kName != NULL);
    LOG_HANDLE_DATA new_data;
    initData<const std::string>(new_data, std::string(kName), std::string(kValue));
    setData(*(LOG_HANDLE_IMPL*)handle, new_data);
    return;
}

void log_handle_serialize_data(size_t buffer_size, char ret_buffer[], const LOG_HANDLE *kHandle)
{
    assert(buffer_size > 0);
    assert(ret_buffer != NULL);
    assert(kHandle != NULL);
    const LOG_HANDLE_IMPL *kImpl = (const LOG_HANDLE_IMPL *)kHandle;

    memset(ret_buffer, 0, buffer_size);
    std::stringstream ss;
    for (size_t i = 0; i < kImpl->used_item_count; i++)
    {
        if (i > 0)
        {
            ss << ",";
        }
        ss << kImpl->items[i].name << "=" << kImpl->items[i].value;
    }

    strncpy(ret_buffer, ss.str().c_str(), buffer_size);
    ret_buffer[buffer_size - 1] = '\0';
    return;
}

