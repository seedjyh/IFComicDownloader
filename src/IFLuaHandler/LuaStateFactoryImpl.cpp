//
//   File name      : LuaStateFactoryImpl.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFLuaHandler
//
//   Create datetime: 2012-04-10 00:53:10
//

// Tested or implemented header
#include "LuaStateFactoryImpl.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
#include "LuaStateImpl.h"

LUA_STATE_PTR LuaStateFactoryImpl::Create() const
{
    return LUA_STATE_PTR(new LuaStateImpl);
}
