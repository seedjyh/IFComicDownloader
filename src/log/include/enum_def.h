//
//   File name      : enum_def.h
//
//   Code by        : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2017-02-15 00:07:47
//

#ifndef _ENUM_DEF_H_
#define _ENUM_DEF_H_ 1

// Inherited header
// ...

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

// 日志严重度，数字越大越严重。
// DEBUG：详细信息，用于排查故障时的打印（进入某个函数、离开某个函数，打印某个变量当前值之类就在此列）
// INFO：用于确认程序正如预定运行的信息（比如读取配置文件、连接到服务器，运行开始等等。）
// WARNING：指定发生了一些预期外的事情（比如预期收到响应消息，但结果定时器超时了还没收到；这意味着自己或远端平台出现异常），
//          或者预见到未来会发生故障（比如磁盘空间快满了）。这个过程中程序仍然在正常运行，并未发生执行预订功能失败的情况。
// ERROR：发生了严重问题，导致程序无法提供某些预订能提供的功能。但程序仍在运行中。
// CRITICAL：发生了严重错误。预示着程序无法继续运行。
enum eLogLevel {
    eLogLevel_Debug = 0,
    eLogLevel_Info = 1,
    eLogLevel_Warning = 2,
    eLogLevel_Error = 3,
    eLogLevel_Critical = 4
};

#endif
