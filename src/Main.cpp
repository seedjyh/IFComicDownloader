//
//   File name      : Main.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-17 11:14:50
//

#ifndef _GTEST_

// Implemented header
// ...

// C system headers
// ...

// C++ system headers
#include <iostream>

// Headers from other projects
#include "IFDataType/IFException.h"

// Headers of current project
#include "GlobalEnum.h"
#include "ProgramArguments.h"
#include "System.h"

static const std::string s_kVersion("0.0.0.1");

int main(int argc, char **argv)
{
    try
    {
        ProgramArguments::Instance().Initialize(argc, argv);
    }
    catch (...)
    {
        return EXIT_FAILURE;
    }

    if (eProgramActionType_ShowVersion == ProgramArguments::Instance().action_type())
    {
        std::cout << s_kVersion << std::endl;
        std::cout << "Build time:\t" << __TIME__ << ", " << __DATE__ << std::endl;
        return EXIT_SUCCESS;
    }
    else if (eProgramActionType_ShowHelp == ProgramArguments::Instance().action_type())
    {
        std::cout << ProgramArguments::Instance().GetArgumentHelp() << std::endl;
        return EXIT_SUCCESS;
    }
    else
    {
        try
        {
            System system;
            system.Run();
        }
        catch (IFException &e)
        {
            std::cout << e.message() << std::endl;
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
}

#endif
