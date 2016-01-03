//
//   File name      : ComicDownloader.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-02 17:53:48
//

#ifndef _COMICDOWNLOADER_H_
#define _COMICDOWNLOADER_H_ 1

// Tested or implemented header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFLuaHandler/LuaState.h"

// Headers of current project
// ...

class Tstring;

class ComicDownloader
{
    LUA_STATE_PTR lua_state_;
public:
    ComicDownloader(LUA_STATE_PTR lua_state)
    :   lua_state_(lua_state){}
    ~ComicDownloader(){}

    void Download(const std::string &kURL, const Tstring &kDownloadRootPath);
protected:
private:
};

#endif
