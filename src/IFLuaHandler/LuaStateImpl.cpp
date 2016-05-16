//
//   File name      : LuaStateImpl.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFLuaHandler
//
//   Create datetime: 2012-04-08 21:47:8
//

// Tested or implemented header
#include "LuaStateImpl.h"

// C system headers
#include <assert.h>
#include <windows.h>
#include <stdarg.h>

// C++ system headers
// ...

// Headers from other projects
#include "IFOperator/CodeTransformer.h"
#include "IFDataType/PathTypes.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFMacros/BasicProcessMacro.h"
#include "Lua.hpp"

// Headers of current project
// ...

LuaStateImpl::LuaStateImpl()
:   state_(NULL){
    state_ = luaL_newstate();
    assert(state_);
    luaL_openlibs(state_);
}

LuaStateImpl::~LuaStateImpl()
{
    if (state_)
    {
        lua_close(state_);
        state_ = NULL;
    }
}

int LuaStateImpl::LoadFile(const Tstring &kFile)
{
    int nResult  = false;
    int nRetCode = false;

    LockerCtrl locker_ctrl(locker_);

    char file_path[MAX_PATH] = {'\0'};

    nRetCode = CodeTransformer::TransTcharToChar(kFile.length(), kFile.c_str(), MY_SIZE_OF_ARRAY(file_path), file_path);
    MY_PROCESS_ERROR(nRetCode);

    nRetCode = luaL_loadfile(state_, file_path);
    MY_PROCESS_ERROR(0 == nRetCode);

    nRetCode = lua_pcall(state_, 0, 0, 0);
    MY_PROCESS_ERROR(0 == nRetCode);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int LuaStateImpl::LoadBuffer(const char kBuffer[])
{
    int nRetCode = false;
    int nResult  = false;

    LockerCtrl locker_ctrl(locker_);

	nRetCode = luaL_loadbuffer(state_, kBuffer, strlen(kBuffer), "chunk name");
	MY_PROCESS_ERROR(0 == nRetCode);

	nRetCode = lua_pcall(state_, 0, 0, 0);
	MY_PROCESS_ERROR(0 == nRetCode);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int LuaStateImpl::CallFunction(const char kFunctionName[], const char kArgumentTypeList[], ...)
{
    int nResult  = false;
    int nRetCode = false;

    LockerCtrl locker_ctrl(locker_);

    va_list vl;
    int in_argument_number  = 0;
    int out_argument_number = 0;

    assert(kFunctionName);
    assert(kArgumentTypeList);

    va_start(vl, kArgumentTypeList);
    lua_getglobal(state_, kFunctionName);

    in_argument_number = 0;

    for (int i = 0; kArgumentTypeList[i] != '\0'; i++)
    {
        if ('>' == kArgumentTypeList[i])
        {
            break;
        }

        switch (kArgumentTypeList[i])
        {
        case 'd':
            lua_pushnumber(state_, va_arg(vl, double) );
            break;
        case 'i':
            lua_pushnumber(state_, va_arg(vl, int) );
            break;
        case 's':
            lua_pushstring(state_, va_arg(vl, const char*) );
            break;
        default:
            MY_PROCESS_ERROR(false);
        }
        in_argument_number++;
    }

    out_argument_number = strlen(kArgumentTypeList) - in_argument_number - strlen(">");

    nRetCode = lua_pcall(state_, in_argument_number, out_argument_number + 1, 0); // +1是为了便于程序回传出错信息。如果程序出错，一定返回[-2]nil和出错信息[-1]string
    MY_PROCESS_ERROR(0 == nRetCode);

    for (int i = in_argument_number + strlen(">"); kArgumentTypeList[i] != '\0'; i++)
    {
        int result_index = i - (in_argument_number + strlen(">") ) + 1; // result_index 从1开始
		int type_enum = lua_type(state_, result_index);
        switch (kArgumentTypeList[i])
        {
        case 'd':
            nRetCode = lua_isnumber(state_, result_index);
            MY_PROCESS_ERROR(nRetCode);

            *va_arg(vl, double*) = lua_tonumber(state_, result_index);
            break;
        case 'i':
            nRetCode = lua_isnumber(state_, result_index);
            MY_PROCESS_ERROR(nRetCode);

            *va_arg(vl, int*) = (int)lua_tonumber(state_, result_index);
            break;
        case 's':
            nRetCode = lua_isstring(state_, result_index);
            // todo: code below could be used in other "case"(s) of this "switch".
            //       and be put into a new independent function.
            if (!nRetCode) // lua function returned 2 values: nil, "error-reason".
            {
                // Jump current argument to store error message into next one.
                va_arg(vl, const char **);
                if (lua_isnil(state_, result_index))
                {
                    const int kErrorMessageIndex = result_index + 1;
                    if (lua_isstring(state_, kErrorMessageIndex))
                    {
                        // try save the error message (string next to nil) to argument
                        const char *kTemp = lua_tostring(state_, kErrorMessageIndex);
                        const char **kReturnedValue = va_arg(vl, const char **);
                        if ((kTemp != NULL) && (kReturnedValue != NULL))
                        {
                            *kReturnedValue = kTemp;
                        }
                    }
                }
                MY_PROCESS_ERROR(false);
            }
            *va_arg(vl, const char**) = lua_tostring(state_, result_index);
            break;
        default:
            MY_PROCESS_ERROR(false);
        }
    }

    lua_pop(state_, out_argument_number + 1);

// Exit1:
    nResult = true;
Exit0:
	if (!nResult)
	{
        if (lua_isstring(state_, 1)) // 系统抛出的错误
        {
            va_arg(vl, void**); // 跳过一个参数
            *va_arg(vl, const char**) = lua_tostring(state_, 1);
        }
		else if (lua_isnil(state_, 1) ) // 自定义的错误
		{
            if (lua_isstring(state_, 2))
            {
                // const char *kErrorLogContent = lua_tostring(state_, 2);
            }
		}
        else
        {
            // 这里还可能有其他情况。
        }
        lua_pop(state_, out_argument_number + 1); // 这一行有必要吗？
	}
    va_end(vl);
    return nResult;
}

const char* LuaStateImpl::ToString(int stack_index)
{
    return lua_tostring(state_, stack_index);
}

void LuaStateImpl::PushString(const std::string &kStr)
{
    lua_pushstring(state_, kStr.c_str() );
    return;
}

void LuaStateImpl::PushNil()
{
    lua_pushnil(state_);
    return;
}

void LuaStateImpl::PushCFunction(lua_CFunction c_function, const std::string &kFunctionNameInLua)
{
    lua_pushcfunction(state_, c_function);
    lua_setglobal(state_, kFunctionNameInLua.c_str() );
    return;
}

void LuaStateImpl::SetGlobal(const std::string &kVariableName)
{
    lua_setglobal(state_, kVariableName.c_str() );
    return;
}

LuaState* LuaStateImpl::Clone()
{
    LockerCtrl locker_ctrl(locker_);

    return new LuaStateImpl(lua_newthread(state_) );
}


LuaStateImpl::LuaStateImpl(lua_State *state)
:   state_(state){
};
