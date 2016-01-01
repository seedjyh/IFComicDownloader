//
//   File name      : LuaStateInterface.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2012-04-12 22:04:12
//

// Tested or implemented header
#include "LuaStateInterface.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFMacros/BasicProcessMacro.h"
#include "IFLuaHandler/LuaState.h"

// Headers of current project
// ...

int LuaStateInterface::GetWorkingThreadCount(LuaState *lua_state, int &count)
{
    int nResult  = false;
    int nRetCode = false;

    nRetCode = lua_state->CallFunction("GetWorkingThreadCount", ">i", &count);
    MY_PROCESS_ERROR(nRetCode);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int LuaStateInterface::GetSiteName(LuaState *lua_state, std::string &ret_name)
{
    int nResult  = false;
    int nRetCode = false;

    const char *kSiteName = NULL;
    nRetCode = lua_state->CallFunction("GetSiteName", ">s", &kSiteName);
    MY_PROCESS_ERROR(nRetCode);

    ret_name = std::string(kSiteName);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}

int LuaStateInterface::GetResourceCoolDownSeconds(LuaState *lua_state, int &count)
{
    int nRetCode = false;
	int nResult  = false;

	nRetCode = lua_state->CallFunction("GetResourceCoolDownSeconds", ">i", &count);
	MY_PROCESS_ERROR(nRetCode);

// Exit1:
    nResult = true;
Exit0:
    return nResult;
}
