//
//   File name      : TestProgramArguments.cpp
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-21 11:11:27
//

#ifdef _GTEST_

// Implemented header
#include "ProgramArguments.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <gtest/gtest.h>

// Headers of current project
#include "IFMacros/BasicOperateMacro.h"

class ArgList
{
    int argc_;
    const char *kArgList_[128];
public:
    ArgList()
    :   argc_(0){}
    void Add(const char *kNewArg)
    {
        if (argc_ >= MY_SIZE_OF_ARRAY(kArgList_))
        {
            throw -1;
        }
        kArgList_[argc_] = kNewArg;
        argc_++;
        return;
    }

    int argc() const { return argc_; }
    const char * const * argv() const { return kArgList_; }
protected:
private:
};

class ArgListCreater
{
    ArgList product_;
public:
    ArgListCreater()
    {
        product_.Add("exe");
    }

    ArgListCreater& operator()(const char *kNewArg)
    {
        product_.Add(kNewArg);
        return *this;
    }

    const ArgList& product() const
    {
        return product_;
    }

protected:
private:
};

static ProgramArguments& DoCreate(const ArgListCreater &kCreater)
{
    ProgramArguments::Instance().Initialize(kCreater.product().argc(), kCreater.product().argv());
    return ProgramArguments::Instance();
}

TEST(ProgramArguments, Initialize_action_type)
{
    ASSERT_EQ(eProgramActionType_Download, DoCreate(ArgListCreater()("-u")("abc")).action_type());
    ASSERT_EQ(eProgramActionType_ShowVersion, DoCreate(ArgListCreater()("-v")).action_type());
    ASSERT_EQ(eProgramActionType_ShowHelp, DoCreate(ArgListCreater()("-h")).action_type());
    ASSERT_EQ(eProgramActionType_JustAnalyse, DoCreate(ArgListCreater()("-a")("-u")("abc")).action_type());
}

#endif
