//
//   File name      : CFunctionForLuaLib.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2012-04-25 13:31:19
//

#ifndef _IFCOMICDOWNLOADER_IFCOMICDOWNLOADER_CFUNCTIONFORLUALIB_H_
#define _IFCOMICDOWNLOADER_IFCOMICDOWNLOADER_CFUNCTIONFORLUALIB_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "Lua.hpp"

// Headers of current project
// ...

class CFunctionForLuaLib
{
public:
    static int Base64Decode(lua_State *state);
    static int TransUtf8ToAnsi(lua_State *state);
    static int TransBigEndianUnicodeToAnsi(lua_State *state);
	static int TransCode(lua_State *state);
	static int DownloadURL(lua_State *state);
	static int WriteLog(lua_State *state);
	static int FormatUrltoUtf8(lua_State *state);
    static int SleepMilliSecond(lua_State *state);
    static int JavascriptEval(lua_State *state);
    static int Print(lua_State *state);
protected:
private:
    CFunctionForLuaLib(){};
    ~CFunctionForLuaLib(){};
};


#endif

