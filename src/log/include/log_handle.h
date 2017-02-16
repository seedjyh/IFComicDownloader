//
//   File name      : log_handle.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : RIG_VSBS
//
//   Create datetime: 2017-02-15 14:02:40
//

#ifndef _LOG_HANDLE_H_
#define _LOG_HANDLE_H_ 1

// Inherited header
// ...

// C system headers
#include <stddef.h>

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "../../os_api/include/data_types.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 记录日志打印固定信息的结构体。
    // 具体字段在头文件里不可见。
    typedef struct
    {
        unsigned char dummy[256];
    }LOG_HANDLE;

    // 初始化LOG_HANDLE。不执行该函数就直接使用，会发生不可预料的问题。
    void log_handle_init(LOG_HANDLE *handle);

    // 设置LOG_HANDLE数据的接口。线程不安全。
    // [ in ] kName: 变量名。可以为空，但过长会导致函数执行失败。
    // [ in ] value: 变量值。
    // 多次设置相同变量名的不同值时，后设置的值会覆盖先设置的值。
    // 设置后的变量会在日志中按照首次设置的顺序打印出来。
    void log_handle_set_int(LOG_HANDLE *handle, const char kName[], int value);
    void log_handle_set_uint64(LOG_HANDLE *handle, const char kName[], ULL value);
    void log_handle_set_string(LOG_HANDLE *handle, const char kName[], const char kValue[]);

    // 将LOG_HANDLE中的所有数据序列化。
    // [ in ] buffer_size: 用于输出的缓冲区大小。
    // [ in, out ] ret_buffer: 用于输出的缓冲区首地址。
    // [ in ] kHandle: 要序列化数据的LOG_HANDLE指针。
    // 如果缓冲区不够大，则仅会填满缓冲区。会确保缓冲区最后一个字节是'\0'。
    void log_handle_serialize_data(size_t buffer_size, char ret_buffer[], const LOG_HANDLE *kHandle);

#ifdef __cplusplus
}
#endif

#endif
