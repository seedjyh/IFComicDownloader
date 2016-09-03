//
//   File name      : TestDownloadInfo.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-01 15:55:25
//

#ifdef _GTEST_

// Tested header
#include "DownloadInfo.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
#include <gtest/gtest.h>

// Headers of current project
// ...

TEST(DownloadInfo, toString)
{
    DownloadInfo info(std::string("Dangan Ronpa"), std::string("http://12.34.56.78/danganronpa/"));
    ASSERT_STREQ(", title=¡¶Dangan Ronpa¡·, url=http://12.34.56.78/danganronpa/", info.toLogLine().c_str() + strlen("time=YYYY-MM-DD hh:mm:ss.xxx"));
}

#endif
