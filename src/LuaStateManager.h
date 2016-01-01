//
//   File name      : LuaStateManager.h
//
//   Code by        : jiangyonghang
//
//   Project name   : IFLuaHandler
//
//   Create datetime: 2012-04-03 10:43:3
//

#ifndef _IFCOMICDOWNLOADER_IFLUAHANDLER_LUASTATEMANAGER_H_
#define _IFCOMICDOWNLOADER_IFLUAHANDLER_LUASTATEMANAGER_H_ 1

// Tested or implemented header
// ...

// C system headers
#include <tchar.h>
#include <windows.h>

// C++ system headers
#include <vector>
#include <string>
#include <map>

// Headers from other projects
#include "IFDataType/Tstring.h"
#include "IFDataType/PathTypes.h"
#include "Lua.hpp"

// Headers of current project
#include "IFLuaHandler/LuaState.h"

class LuaStateFactory;
class ProcessResourceManagerNoDB;
class DirectoryTree;
class UrlDownloaderFactory;

typedef struct SiteInfo{
	std::string host_URL_;
	Tstring     script_directory_;
	SiteInfo():host_URL_(""){};
	SiteInfo(const std::string &kHostURL, const Tstring &kScriptDirectory)
	:	host_URL_(kHostURL),
	script_directory_(kScriptDirectory){};
}SiteInfo;

typedef std::map<std::string, SiteInfo> SiteNameInfoMap;

//  Save all lua script files into RAM in the first loading.
//  Create one lua-state for each site to identify the site name of a URL.
//  When caller needs a new lua-state, create a new state and load necessary
//      lua-script from RAM (root_script_directory_tree_).

class LuaStateManager
{
    Tstring root_path_;
    LuaStateFactory *state_factory_;
    std::vector<LUA_STATE_PTR> state_list_; // URL --> site name
    SiteNameInfoMap sitename_to_info_;  // site name --> siteinfo(host URL, Script Path)
    DirectoryTree *root_script_directory_tree_;

public:
    LuaStateManager(const Tstring &kRootPath);
    ~LuaStateManager();

    // 3 methods to reload all lua scripts from different source.
    void ReloadScriptsFromDirectory(const Tstring &kRootScriptPath);

    // other methods.
    void ReadEntireScriptDirectory(const Tstring &kRootScriptPath);

	const SiteNameInfoMap& sitename_to_info() const {return sitename_to_info_;}

    static PathList GetAllSiteLuaDirectory(const Tstring &kRootPath);

    static void LoadDirectory(LUA_STATE_PTR state, const Tstring &kPath);

    static void LoadDirectoryTree(LUA_STATE_PTR state, const DirectoryTree *kDirectoryTree);

    static bool IsLuaFile(const Tstring &kFile);

    static std::string GetSiteName(LUA_STATE_PTR state);

    static std::string GetSiteHostURL(LUA_STATE_PTR state);

    static void LoadCFunction(LUA_STATE_PTR state, lua_CFunction c_function, const std::string &kFunctionNameInLua);

    static void LoadCFunctionLib(LUA_STATE_PTR state);

    void LoadLuaAPI(LUA_STATE_PTR state) const;

    void LoadOneSite(LUA_STATE_PTR state, const std::string &kSiteName) const;

    void LoadSites();

    std::string GetSiteNameByURL(const std::string &kURL);

    LUA_STATE_PTR GetStateBySiteName(const std::string &kSiteName) const;

protected:
private:
};

#endif