//
//   File name      : LuaStateFactory.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFLuaHandler
//
//   Create datetime: 2012-04-10 00:40:10
//

#ifndef _IFCOMICDOWNLOADER_IFLUAHANDLER_INCLUDE_LUASTATEFACTORY_H_
#define _IFCOMICDOWNLOADER_IFLUAHANDLER_INCLUDE_LUASTATEFACTORY_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "LuaState.h"

class LuaStateFactory
{
public:
    LuaStateFactory(){};
    virtual ~LuaStateFactory(){};

    virtual LUA_STATE_PTR Create() const = 0;
protected:
private:
};

#endif