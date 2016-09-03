//
//   File name      : SystemTimeFactory.h
//
//   Code by        : jiangyonghang
//
//   Project name   : FindNoServerLite
//
//   Create datetime: 2010-10-22 11:11:15
//

#ifndef _FINDNOSERVERLITE_SYSTEMTIMEFACTORY_H_
#define _FINDNOSERVERLITE_SYSTEMTIMEFACTORY_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFMacros/DevelopMacros.h"

// Headers of current project
// ...

class SystemTime;

class SystemTimeFactory
{
public:
    // 在Windows下达不到微秒级，只能达到毫秒级
    static SystemTime* CreateLocalTime();

    static SystemTime* CreateSpecificTime(
        unsigned int year,
        unsigned int month,
        unsigned int day,
        unsigned int hour,
        unsigned int minute,
        unsigned int second,
        unsigned int microsecond,
        unsigned int day_of_week
    );

    static SystemTime* CreateFromTime(const SystemTime *kSrcTime);

    static SystemTime* CreateTimeFromOffsetSecond(unsigned int second_from_1900);
protected:
private:
    SystemTimeFactory(){};
    ~SystemTimeFactory(){};
    DISALLOW_COPY_AND_ASSIGN(SystemTimeFactory);
};

#endif

