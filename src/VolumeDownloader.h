//
//   File name      : VolumeDownloader.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-01-03 06:43:51
//

#ifndef _VOLUMEDOWNLOADER_H_
#define _VOLUMEDOWNLOADER_H_ 1

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

class VolumeDownloader
{
    LUA_STATE_PTR lua_state_;
    std::string comic_title_;
public:
    VolumeDownloader(LUA_STATE_PTR lua_state)
    :   lua_state_(lua_state){}
    ~VolumeDownloader(){}

    void set_comic_title(const std::string &kTitle) { comic_title_ = kTitle; return; }
    void Download(const std::string &kURL, const Tstring &kDownloadRootPath);
protected:
private:
};

#endif
