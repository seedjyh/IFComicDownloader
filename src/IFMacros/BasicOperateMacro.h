//
//   File name      : BasicOperateMacro.h.h
//
//   Code by        : jiangyonghang
//
//   Project name   : BasicMacro
//
//   Create datetime: 2010-09-29 09:43:23
//


#ifndef _BASICOPERATEMACRO_H_
#define _BASICOPERATEMACRO_H_ 1

#include "stddef.h"

#define MY_DELETE(p)        \
    do                      \
    {                       \
        if (p)              \
        {                   \
            delete p;       \
            p = NULL;       \
        }                   \
    }while(false)

#define MY_DELETEARRAY(p)   \
    do                      \
    {                       \
        if (p)              \
        {                   \
            delete []p;     \
            p = NULL;       \
        }                   \
    } while(false)

#define MY_FCLOSE(p)        \
    do                      \
    {                       \
        if (p)              \
        {                   \
            fclose(p);      \
            p = NULL;       \
        }                   \
    } while(false)

#define MY_REMOVE_TAIL_NEWLINE(str) \
    do                              \
    {                               \
        size_t uLen = strlen(str);  \
        if ('\n' == str[uLen - 1])  \
        {                           \
            str[uLen - 1] = '\0';   \
        }                           \
    } while (false)

#define MY_SIZE_OF_ARRAY(a) \
    (sizeof(a)/sizeof(a[0]))

#define MY_SET_TAIL_NULL(str)               \
    do                                      \
    {                                       \
    str[MY_SIZE_OF_ARRAY(str) - 1] = '\0';  \
    } while (false)

#define MY_CLOSE_HANDLE(h)                  \
    do                                      \
    {                                       \
        if (h != INVALID_HANDLE_VALUE)      \
        {                                   \
            CloseHandle(h);                 \
            h = INVALID_HANDLE_VALUE;       \
        }                                   \
    } while (false);


#define MY_FINDCLOSE(h)                     \
    do                                      \
    {                                       \
        if (h != INVALID_HANDLE_VALUE)      \
        {                                   \
            FindClose(h);                   \
            h = INVALID_HANDLE_VALUE;       \
        }                                   \
    } while (false);


#endif
