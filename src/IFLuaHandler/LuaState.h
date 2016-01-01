//
//   File name      : LuaState.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFLuaHandler
//
//   Create datetime: 2012-04-08 21:10:8
//

#ifndef _IFCOMICDOWNLOADER_IFLUAHANDLER_INCLUDE_LUASTATE_H_
#define _IFCOMICDOWNLOADER_IFLUAHANDLER_INCLUDE_LUASTATE_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <string>

// Headers from other projects
#include <boost/shared_ptr.hpp>

// Headers of current project
#include "Lua.hpp"

class Tstring;

class LuaState
{
public:
    LuaState(){};
    virtual ~LuaState(){};

    virtual int LoadFile(const Tstring &kFile) = 0;

	virtual int LoadBuffer(const char kBuffer[]) = 0;

    virtual int CallFunction(const char kFunctionName[], const char kArgumentTypeList[], ...) = 0;

    virtual const char* ToString(int stack_index) = 0;
    virtual void PushString(const std::string &kStr) = 0;
    virtual void PushNil() = 0;
    virtual void PushCFunction(lua_CFunction c_function, const std::string &kFunctionNameInLua) = 0;
    virtual void SetGlobal(const std::string &kVariableName) = 0;

    virtual LuaState* Clone() = 0;
protected:
private:
};

typedef boost::shared_ptr<LuaState> LUA_STATE_PTR;

#endif