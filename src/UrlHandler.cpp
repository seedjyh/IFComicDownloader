//
//   File name      : UrlHandler.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-29 08:53:05
//

// Implemented header
#include "UrlHandler.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include "IFDataType/Tstring.h"
#include "IFOperator/PathHandler.h"

// Headers of current project
#include "exception/UrlAnalyseFailedException.h"
#include "LuaStateManager.h"
#include "ComicDownloader.h"

UrlHandler::UrlHandler(LuaStateManager &lua_state_manager)
:   lua_state_manager_(lua_state_manager){}

XML UrlHandler::Analyse(const std::string &kURL)
{
    std::string site_name = lua_state_manager_.GetSiteNameByURL(kURL);

    const char *kAnalyseResult = NULL;
    const char *kErrorMessage = NULL;
    LUA_STATE_PTR state = lua_state_manager_.GetStateBySiteName(site_name);
    if (!state->CallFunction("Analyse", "s>s", kURL.c_str(), &kAnalyseResult, &kErrorMessage))
    {
        throw UrlAnalyseFailedException(kURL, std::string("call lua function \"Analyse\" failed") + "\nbecause: " + ((kErrorMessage != NULL)?kErrorMessage:""));
    }
    // If you don't declare @state outside of the if(), the value pointed by @kAnalyseResult would lost before storing it to a XML
    // because state was automatically destructed.
    return XML(kAnalyseResult);
}

void UrlHandler::HandleRecursively(const std::string &kURL, const Tstring &kDownloadRootPath)
{
    if (!PathHandler::CreatePath(kDownloadRootPath))
    {
        throw 1;
    }
    ComicDownloader downloader(lua_state_manager_.GetStateBySiteName(lua_state_manager_.GetSiteNameByURL(kURL)));
    downloader.Download(kURL, kDownloadRootPath);
    return;
}
