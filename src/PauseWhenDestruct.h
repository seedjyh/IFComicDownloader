//
//   File name      : PauseWhenDestruct.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-21 11:09:58
//

#ifndef _PAUSEWHENDESTRUCT_H_
#define _PAUSEWHENDESTRUCT_H_

// Inherite header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

// This class will pause the program while been destructed so that programmer
// could read the output in CLI.

class PauseWhenDestruct
{
public:
    PauseWhenDestruct(){}
    ~PauseWhenDestruct()
    {
        system("pause");
    }
protected:
private:
};

#endif
