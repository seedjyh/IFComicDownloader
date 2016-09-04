//
//   File name      : System.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-21 14:14:39
//

// Implemented header
#include "System.h"

// C system headers
// ...

// C++ system headers
#include <iostream>

// Headers from other projects
// ...

// Headers of current project
#include "CacheManager.h"
#include "UrlHandler.h"
#include "LuaStateManager.h"
#include "ProgramArguments.h"
#include "PythonInterface.h"

void System::Run()
{
    CacheManager::set_cache_directory_path(ProgramArguments::Instance().cache_path());
    LuaStateManager lua_state_manager(ProgramArguments::Instance().script_path());
    PythonInterface python_interface;

    UrlHandler handler(lua_state_manager);
    if (eProgramActionType_JustAnalyse == ProgramArguments::Instance().action_type())
    {
        std::cout << handler.Analyse(ProgramArguments::Instance().target_url()) << std::endl;
    }
    else if (eProgramActionType_Download == ProgramArguments::Instance().action_type())
    {
        handler.HandleRecursively(ProgramArguments::Instance().target_url(), ProgramArguments::Instance().download_path());
    }
    return;
}
