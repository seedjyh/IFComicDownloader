//
//   File name      : LuaStateInterface.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2012-04-12 22:01:12
//

#ifndef _IFCOMICDOWNLAODER_IFCOMICDOWNLOADER_SRC_LUASTATEINTERFACE_H_
#define _IFCOMICDOWNLAODER_IFCOMICDOWNLOADER_SRC_LUASTATEINTERFACE_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <string>

// Headers from other projects
// ...

// Headers of current project
// ...

class LuaState;

class LuaStateInterface
{
public:
    static int GetWorkingThreadCount(LuaState *lua_state, int &count);
    static int GetSiteName(LuaState *lua_state, std::string &ret_name);
	static int GetResourceCoolDownSeconds(LuaState *lua_state, int &count);
protected:
private:
    LuaStateInterface(){};
    ~LuaStateInterface(){};
};

#endif