//
//   File name      : ProgramArguments.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-18 15:41:10
//

// Implemented header
#include "ProgramArguments.h"

// C system headers
#include <windows.h>

// C++ system headers
#include <sstream>

// Headers from other projects
// ...

// Headers of current project
#include "IFMacros/BasicOperateMacro.h"
#include "IFDataType/Tstring.h"
#include "IFOperator/CodeTransformer.h"

ProgramArguments* ProgramArguments::instance_ = NULL;

ProgramArguments& ProgramArguments::Instance()
{
    if (NULL == instance_)
    {
        instance_ = new ProgramArguments();
    }
    return *instance_;
}

void ProgramArguments::Initialize(int argc, const char * const *argv)
{
    Tstring root_path = GetRootPath();

    boost::program_options::variables_map option_map;

    try
    {
        store(parse_command_line(argc, argv, option_desc_), option_map);
    }
    catch (std::exception &e)
    {
        throw std::string(e.what() );
    }
    notify(option_map);

    if (option_map.count("help"))
    {
        action_type_ = eProgramActionType_ShowHelp;
        return;
    }

    if (option_map.count("version"))
    {
        action_type_ = eProgramActionType_ShowVersion;
        return;
    }

    if (option_map.count("analyse"))
    {
        action_type_ = eProgramActionType_JustAnalyse;
    }
    else
    {
        action_type_ = eProgramActionType_Download;
    }

    if (option_map.count("url"))
    {
        target_url_ = option_map["url"].as<std::string>();
    }
    else
    {
        throw std::string("No URL, program will exit.");
    }

    if (option_map.count("download-path"))
    {
        if (!CodeTransformer::TransStringToTString(option_map["download-path"].as<std::string>(), download_path_))
        {
            throw std::string("Reading argument download-path failed");
        }
    }
    else
    {
        download_path_ = root_path + TEXT("download\\");
    }

    if (option_map.count("script-path"))
    {
        if (!CodeTransformer::TransStringToTString(option_map["script-path"].as<std::string>(), script_path_))
        {
            throw std::string("Reading argument script-path failed");
        }
    }
    else
    {
        script_path_ = root_path + TEXT("script\\");
    }

    if (option_map.count("cache-path"))
    {
        if (!CodeTransformer::TransStringToTString(option_map["cache-path"].as<std::string>(), cache_path_))
        {
            throw std::string("Reading argument redirect-path failed.");
        }
    }
    else
    {
        cache_path_ = root_path + TEXT("cache\\");
    }
    return;
}

std::string ProgramArguments::GetArgumentHelp() const
{
    std::stringstream ss;
    ss << option_desc_;
    return ss.str();
}

ProgramArguments::ProgramArguments()
:   option_desc_("command line options"),
    curl_dll_path_(_T("libcurl.dll"))
{
    option_desc_.add_options()
        ("help,h", "print this message")
        ("version,v", "print version of VXI")
        ("analyse,a", "just analyse the page")
        ("url,u", boost::program_options::value<std::string>(), "target URL to download and analyse.")
        ("download-path,d", boost::program_options::value<std::string>(), "root path for saving downloaded files")
        ("script-path,s", boost::program_options::value<std::string>(), "the root path of lua script")
        ("cache-path,c", boost::program_options::value<std::string>(), "the root path of cache system, including cache list file and all temporary files")
        ;
}

Tstring ProgramArguments::GetRootPath()
{
    TCHAR buffer[MAX_PATH];
    if (0 == GetModuleFileName(NULL, buffer, MY_SIZE_OF_ARRAY(buffer)))
    {
        throw std::string("Get module(exe) path failed.");
    }

    // 现在buffer里保存着.exe文件的全路径。
    TCHAR *loc = _tcsrchr(buffer, '\\');
    if (loc != NULL)
    {
        *(loc) = '\0';
    }
    // 现在buffer里保存着.exe所在目录的路径（末尾没有'\\'）。这个路径应该是一个名字为“bin”的文件夹。
    loc = _tcsrchr(buffer, '\\');
    if (loc != NULL)
    {
        *(loc) = '\0';
    }
    // 现在buffer里保存着.exe所在路径再上一级的路径。这个路径下有两个目录：“bin”和“script”。
    _tcscat(buffer, _T("\\"));
    return Tstring(buffer);
}
