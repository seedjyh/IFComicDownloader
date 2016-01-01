//
//   File name      : LuaStateFactoryImpl.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFLuaHandler
//
//   Create datetime: 2012-04-10 00:50:10
//

#ifndef _IFCOMICDOWNLOADER_IFLUAHANDLER_SRC_LUASTATEFACTORYIMPL_H_
#define _IFCOMICDOWNLOADER_IFLUAHANDLER_SRC_LUASTATEFACTORYIMPL_H_ 1

// Tested or implemented header
#include "LuaStateFactory.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class LuaStateFactoryImpl: public LuaStateFactory
{
public:
    LuaStateFactoryImpl(){};
    virtual ~LuaStateFactoryImpl(){};

    virtual LUA_STATE_PTR Create() const;
protected:
private:
};

#endif