//
//   File name      : SleepMacro.h
//
//   Code by        : jiangyonghang
//
//   Project name   : FindNoServerLite
//
//   Create datetime: 2010-10-29 09:47:51
//

#ifndef _FINDNOSERVERLITE_SLEEPMACRO_H_
#define _FINDNOSERVERLITE_SLEEPMACRO_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

#if defined WIN32
#include <windows.h>
#define SLEEP_MS(x) Sleep(x)

#elif defined linux

#define SLEEP_MS(x)                             \
    do                                          \
    {                                           \
        struct timeval timeWait;                \
        timeWait.tv_sec  = x / 1000;            \
        timeWait.tv_usec = x % 1000 * 1000;     \
        select(0, NULL, NULL, NULL, &timeWait); \
    } while (false)

#endif

#endif
