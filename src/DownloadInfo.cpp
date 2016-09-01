//
//   File name      : DownloadInfo.cpp
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2016-09-01 15:32:09
//

// Inherited header
#include "DownloadInfo.h"

// C system headers
// ...

// C++ system headers
#include <boost/shared_ptr.hpp>

// Headers from other projects
// ...

// Headers of current project
#include "IFDataType/SystemTimeFactory.h"
#include "IFDataType/SystemTime.h"
#include "IFMacros/BasicOperateMacro.h"

const std::string DownloadInfo::toLogLine() const
{
    char buffer[1024] = { '\0' };

    boost::shared_ptr<SystemTime> now(SystemTimeFactory::CreateLocalTime());

    _snprintf(
        buffer, MY_SIZE_OF_ARRAY(buffer),
        "time=%s, title=¡¶%s¡·, url=%s",
        now->toString().c_str(),
        comic_title_.c_str(),
        comic_url_.c_str()
        );
    MY_SET_TAIL_NULL(buffer);

    return std::string(buffer);
}
