/*
*    File name      : Locker.cpp
*
*    Code by        : jiangyonghang
*
*    Project name   : Thread Locker
*
*    Create datetime: 2009-05-31 10:36:55
*/

#include <assert.h>
#include "Locker.h"

Locker::Locker()
{
#if defined WIN32
    InitializeCriticalSection(&mutex_); 
#elif defined linux
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&mutex_, &attr);
#endif

}

void Locker::Lock()
{
#if defined WIN32
    EnterCriticalSection(&mutex_);
#elif defined linux
    pthread_mutex_lock(&mutex_);
#endif

    return;
}

void Locker::Unlock()
{
#if defined WIN32
    LeaveCriticalSection(&mutex_);
#elif defined linux
    pthread_mutex_unlock(&mutex_);
#endif


    return;
}

