//
//   File name      : BasicProcessMacro.h
//
//   Code by        : jiangyonghang
//
//   Project name   : 
//
//   Create datetime: 2010-09-29 10:09:26
//

#ifndef _BASICPROCESSMACRO_H_
#define _BASICPROCESSMACRO_H_ 1

#define MY_PROCESS_ERROR(x)     \
    do                          \
    {                           \
        if (!(x) )               \
            goto Exit0;         \
    }while(false)

#define MY_PROCESS_SUCCESS(x)   \
    do                          \
    {                           \
        if (x)                  \
            goto Exit1;         \
    }while(false)

#define MY_RETURN_ERROR(x, y)   \
    do                          \
    {                           \
        if (!(x) )              \
        {                       \
            nResult = y;        \
            goto Exit0;         \
        }                       \
    } while (false);

#define MY_RETURN_SUCCESS(x, y) \
    do                          \
    {                           \
        if (x)                  \
        {                       \
            nResult = y;        \
            goto Exit1;         \
        }                       \
    } while (false);

#endif

