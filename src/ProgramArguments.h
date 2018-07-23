//
//   File name      : ProgramArguments.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-18 14:39:31
//

#ifndef _PROGRAMARGUMENTS_H_
#define _PROGRAMARGUMENTS_H_ 1

// Inherite header
// ...

// C system headers
// ...

// C++ system headers
#include <boost/program_options.hpp>
#include <string>

// Headers from other projects
// ...

// Headers of current project
#include "GlobalEnum.h"
#include "IFDataType/Tstring.h"

// Use Singleton pattern.

class ProgramArguments
{
    static ProgramArguments *instance_;

    boost::program_options::options_description option_desc_;

    eProgramActionType action_type_;
    std::string target_url_;
	std::string proxy_url_;
    Tstring download_path_;
    Tstring script_path_;
    Tstring cache_path_;
    Tstring curl_dll_path_;
public:
    static ProgramArguments& Instance();

    void Initialize(int argc, const char * const *argv);
    std::string GetArgumentHelp() const;

	eProgramActionType action_type() const { return action_type_; }
	const std::string& target_url() const { return target_url_; }
	const std::string& proxy_url() const { return proxy_url_; }
    const Tstring& download_path() const { return download_path_; }
    const Tstring& script_path() const { return script_path_; }
    const Tstring& cache_path() const { return cache_path_; }
    const Tstring& curl_dll_path() const { return curl_dll_path_; }
protected:
private:
    ProgramArguments();
    ~ProgramArguments(){}
    static Tstring GetRootPath();
};

#endif
