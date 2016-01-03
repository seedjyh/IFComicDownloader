//
//   File name      : UrlHandler.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-22 16:49:16
//

#ifndef _URLHANDLER_H_
#define _URLHANDLER_H_

// Inherite header
// ...

// C system headers
// ...

// C++ system headers
#include <string>

// Headers from other projects
// ...

// Headers of current project
#include "IFDataType/Tstring.h"

class LuaStateManager;
class UrlDownloaderFactory;

typedef std::string XML;

class UrlHandler
{
    LuaStateManager &lua_state_manager_;
public:
    UrlHandler(LuaStateManager &lua_state_manager);
    ~UrlHandler(){}

    XML Analyse(const std::string &kURL);

    void HandleRecursively(const std::string &kURL, const Tstring &kDownloadRootPath);
protected:
private:
};

#endif
