/*
*    File name      : Locker.h
*
*    Code by        : jiangyonghang
*
*    Project name   : Thread Locker
*
*    Create datetime: 2009-05-31 10:35:56
*/
#ifndef _FINDNOSERVER_LOCKER_LOCKER_H_
#define _FINDNOSERVER_LOCKER_LOCKER_H_ 1

// The lock could be locked for more than once in a single thread.
// And of course, it should be unlocked for the same times in the same thread after that. 

#if defined WIN32
#include <windows.h>
#elif defined linux
#include <pthread.h>
#endif

#include "IFMacros/DevelopMacros.h"

class Locker
{
#if defined WIN32
    CRITICAL_SECTION
#elif defined linux
    pthread_mutex_t
#endif
    mutex_;
public:
    Locker();
    void Lock();
    void Unlock();
protected:
private:
    DISALLOW_COPY_AND_ASSIGN(Locker);
};

class LockerCtrl
{
    Locker &lock_;
public:
    LockerCtrl(Locker &lock)
    :   lock_(lock)
    {
        lock_.Lock();
    }
    ~LockerCtrl()
    {
        lock_.Unlock();
    }
protected:
private:
    DISALLOW_COPY_AND_ASSIGN(LockerCtrl);
};

#endif

