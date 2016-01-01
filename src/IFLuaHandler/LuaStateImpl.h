//
//   File name      : LuaStateImpl.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFLuaHandler
//
//   Create datetime: 2012-04-08 21:29:8
//

#ifndef _IFCOMICDOWNLOADER_IFLUAHANDLER_SRC_LUASTATEIMPL_H_
#define _IFCOMICDOWNLOADER_IFLUAHANDLER_SRC_LUASTATEIMPL_H_ 1

// Tested or implemented header
#include "LuaState.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFDataType/Locker.h"

// Headers of current project
#include "lua.hpp"

class LuaStateImpl: public LuaState
{
    lua_State *state_;
    Locker locker_;
public:
    LuaStateImpl();
    virtual ~LuaStateImpl();

    virtual int LoadFile(const Tstring &kFile);

	virtual int LoadBuffer(const char kBuffer[]);

    //  Return true if success.
    //  Send an extra "const char **" into this function, more than specified in @kFunctionName.
    //  When this function returns false, caller could get some information from the extra argument.
    virtual int CallFunction(const char kFunctionName[], const char kArgumentTypeList[], ...);

    virtual const char* ToString(int stack_index);
    virtual void PushString(const std::string &kStr);
    virtual void PushNil();
    virtual void PushCFunction(lua_CFunction c_function, const std::string &kFunctionNameInLua);
    virtual void SetGlobal(const std::string &kVariableName);

    virtual LuaState* Clone();

protected:
private:
    LuaStateImpl(lua_State *state);
};

#endif