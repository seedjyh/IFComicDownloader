//
//   File name      : LuaStateManager.cpp
//
//   Code by        : jiangyonghang
//
//   Project name   : IFLuaHandler
//
//   Create datetime: 2012-04-03 11:48:3
//

// Tested or implemented header
#include "LuaStateManager.h"

// C system headers
#include <windows.h>
#include <assert.h>

// C++ system headers
// ...

// Headers from other projects
#include "IFOperator/PathHandler.h"
#include "IFMacros/BasicOperateMacro.h"
#include "IFLuaHandler/LuaState.h"
#include "IFLuaHandler/LuaStateFactory.h"
#include "IFOperator/DirectoryTreeLoader.h"
#include "IFDataType/DirectoryTree.h"
#include "IFDataType/FileHolder.h"
#include "IFLuaHandler/LuaStateFactoryImpl.h"
#include "IFMacros/BasicProcessMacro.h"

// Headers of current project
#include "LuaStateInterface.h"
#include "CFunctionForLuaLib.h"
#include "exception/UnsupportedSiteException.h"
#include "exception/LoadLuaFileFailedException.h"

LuaStateManager::LuaStateManager(const Tstring &kRootPath)
:   root_path_(kRootPath),
    root_script_directory_tree_(NULL),
    state_factory_(NULL)
{
    state_factory_ = new LuaStateFactoryImpl();
    if (NULL == state_factory_)
    {
        throw std::string("Constructor of LuaStateFactoryImpl failed.");
    }
    state_list_.clear();
    sitename_to_info_.clear();
    ReloadScriptsFromDirectory(kRootPath);
}

LuaStateManager::~LuaStateManager()
{
    state_list_.clear();
    sitename_to_info_.clear();
    MY_DELETE(state_factory_);
    MY_DELETE(root_script_directory_tree_);
}

void LuaStateManager::ReloadScriptsFromDirectory(const Tstring &kRootScriptPath)
{
    ReadEntireScriptDirectory(kRootScriptPath);
    LoadSites();
    return;
}

void LuaStateManager::ReadEntireScriptDirectory(const Tstring &kRootScriptPath)
{
    MY_DELETE(root_script_directory_tree_);

    root_script_directory_tree_ = DirectoryTreeLoader::Load(kRootScriptPath);
    if (NULL == root_script_directory_tree_)
    {
        throw 1;
    }

    return;
}

PathList LuaStateManager::GetAllSiteLuaDirectory(const Tstring &kRootPath)
{
    PathList file_list;
    PathList directory_list;

    if (!PathHandler::List(kRootPath, file_list, directory_list))
    {
        throw 1;
    }

    return directory_list;
}

void LuaStateManager::LoadDirectory(LUA_STATE_PTR state, const Tstring &kPath)
{
    PathList file_list;
    PathList directory_list;

    file_list.clear();
    directory_list.clear();
    if (!PathHandler::List(kPath, file_list, directory_list))
    {
        throw 1;
    }

    for (int i = 0; i < static_cast<int>(file_list.size() ); i++)
    {
        if (!IsLuaFile(file_list[i]) )
        {
            continue;
        }

        if (!state->LoadFile(file_list[i]))
        {
            throw 1;
        }
    }

    for (int i = 0; i < static_cast<int>(directory_list.size() ); i++)
    {
        LoadDirectory(state, directory_list[i]);
    }

    return;
}

void LuaStateManager::LoadDirectoryTree(LUA_STATE_PTR state, const DirectoryTree *kDirectoryTree)
{
    for (int i = 0; i < kDirectoryTree->GetChildFileCount(); i++)
    {
        const FileHolder *kScriptFile = kDirectoryTree->GetChildFile(i);
        if (!IsLuaFile(kScriptFile->name() ) )
        {
            continue;
        }

        std::string file_content(kScriptFile->content(), kScriptFile->size() );
        if (!state->LoadBuffer(file_content.c_str()))
        {
            throw LoadLuaFileFailedException(kScriptFile->name());
        }
    }

    for (int i = 0; i < kDirectoryTree->GetChildDirectoryCount(); i++)
    {
        LoadDirectoryTree(state, kDirectoryTree->GetChildDirectory(i));
    }

    return;
}

bool LuaStateManager::IsLuaFile(const Tstring &kFile)
{
    static const Tstring &s_kLuaFileSuffix(TEXT(".lua") );

    if (kFile.size() < s_kLuaFileSuffix.size() )
    {
        return false;
    }

    if (_tcscmp(kFile.c_str() + kFile.size() - s_kLuaFileSuffix.size(), s_kLuaFileSuffix.c_str() ) )
    {
        return false;
    }

    return true;
}

std::string LuaStateManager::GetSiteName(LUA_STATE_PTR state)
{
    const char *kSiteName = NULL;
    if (!state->CallFunction("GetSiteName", ">s", &kSiteName))
    {
        throw 1;
    }

    if (NULL == kSiteName)
    {
        throw 2;
    }

    return std::string(kSiteName);
}

std::string LuaStateManager::GetSiteHostURL(LUA_STATE_PTR state)
{
    const char *kSiteHostURL = NULL;
    if (!state->CallFunction("GetSiteHostURL", ">s", &kSiteHostURL))
    {
        throw 1;
    }

    if (NULL == kSiteHostURL)
    {
        throw 2;
    }
    
    return std::string(kSiteHostURL);
}

void LuaStateManager::LoadCFunction(LUA_STATE_PTR state, lua_CFunction c_function, const std::string &kFunctionNameInLua)
{
    state->PushCFunction(c_function, kFunctionNameInLua.c_str() );
    return;
}

void LuaStateManager::LoadCFunctionLib(LUA_STATE_PTR state)
{
    LoadCFunction(state, CFunctionForLuaLib::Base64Decode, std::string("Base64Decode") );
    LoadCFunction(state, CFunctionForLuaLib::TransUtf8ToAnsi, std::string("TransUtf8ToAnsi") );
    LoadCFunction(state, CFunctionForLuaLib::TransBigEndianUnicodeToAnsi, std::string("TransBigEndianUnicodeToAnsi") );
	LoadCFunction(state, CFunctionForLuaLib::WriteLog, std::string("WriteLog") );
	LoadCFunction(state, CFunctionForLuaLib::FormatUrltoUtf8, std::string("FormatUrltoUtf8") );
	LoadCFunction(state, CFunctionForLuaLib::TransCode, std::string("TransCode") );
	LoadCFunction(state, CFunctionForLuaLib::SleepMilliSecond, std::string("SleepMilliSecond") );
    LoadCFunction(state, CFunctionForLuaLib::DownloadURL, std::string("DownloadURL"));
    LoadCFunction(state, CFunctionForLuaLib::JavascriptEval, std::string("JavascriptEval"));
    LoadCFunction(state, CFunctionForLuaLib::Print, std::string("Print"));
    return;
}

void LuaStateManager::LoadLuaAPI(LUA_STATE_PTR state) const
{
    const DirectoryTree *kTempDir = root_script_directory_tree_->GetChildDirectory(Tstring(TEXT("api")));
    if (NULL == kTempDir)
    {
        throw 1;
    }

    LoadDirectoryTree(state, kTempDir);

    return;
}

void LuaStateManager::LoadOneSite(LUA_STATE_PTR state, const std::string &kSiteName) const
{
    Tstring site_dir_name;
    SiteNameInfoMap::const_iterator kIte;

    kIte = sitename_to_info_.find(kSiteName);
    if (sitename_to_info_.end() == kIte)
    {
        throw 1;
    }

    site_dir_name = kIte->second.script_directory_;

    const DirectoryTree *kTempDir = root_script_directory_tree_->GetChildDirectory(Tstring(TEXT("sites")));
    if (NULL == kTempDir)
    {
        throw 1;
    }

    kTempDir = kTempDir->GetChildDirectory(site_dir_name);
    if (NULL == kTempDir)
    {
        throw 1;
    }

    LoadDirectoryTree(state, kTempDir);

    return;
}

void LuaStateManager::LoadSites()
{
    const DirectoryTree *kSitesDir = root_script_directory_tree_->GetChildDirectory(Tstring(TEXT("sites") ) );
    if (NULL == kSitesDir)
    {
        throw 1;
    }

    state_list_.clear();
    for (int i = 0; i < kSitesDir->GetChildDirectoryCount(); i++)
    {
        LUA_STATE_PTR new_state = state_factory_->Create();

        LoadCFunctionLib(new_state);
        LoadLuaAPI(new_state);
        LoadDirectoryTree(new_state, kSitesDir->GetChildDirectory(i) );

        sitename_to_info_[GetSiteName(new_state)] = SiteInfo(GetSiteHostURL(new_state), kSitesDir->GetChildDirectory(i)->name());

        state_list_.push_back(new_state);
    }

    return;
}

std::string LuaStateManager::GetSiteNameByURL(const std::string &kURL)
{
    for (int i = 0; i < static_cast<int>(state_list_.size() ); i++)
    {
        int check_result = 0;
        if (!state_list_[i]->CallFunction("SiteCheck", "s>i", kURL.c_str(), &check_result))
        {
            throw 1;
        }
        if (check_result)
        {
            return GetSiteName(state_list_[i]);
        }
    }

    throw UnsupportedSiteException(kURL);
}

LUA_STATE_PTR LuaStateManager::GetStateBySiteName(const std::string &kSiteName) const
{
    const DirectoryTree *kTempDir = NULL;

    SiteNameInfoMap::const_iterator kIte = sitename_to_info_.find(kSiteName);
    if (sitename_to_info_.end() == kIte)
    {
        throw 1;
    }

    Tstring site_dir_name = kIte->second.script_directory_;

    LUA_STATE_PTR result = state_factory_->Create();

    LoadCFunctionLib(result);
    LoadLuaAPI(result);

    // load specific site script files.
    kTempDir = root_script_directory_tree_->GetChildDirectory(TEXT("sites") );
    if (NULL == kTempDir)
    {
        throw 1;
    }

    kTempDir = kTempDir->GetChildDirectory(site_dir_name);
    if (NULL == kTempDir)
    {
        throw 1;
    }

    LoadDirectoryTree(result, kTempDir);

    return result;
}
