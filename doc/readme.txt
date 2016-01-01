编译方式：
使用Visual Studio 2013。
本项目目前有两种编译模式：
Debug模式生成可用的程序exe，使用lua、libcurl、gzip库，编译时需要它们的lib，运行时需要它们的dll。
DebugGoogleTest模式是单元测试模式，除了上述的库之外，还使用googletest库。

命令行调试方式：
调试时要注意的点：
在Visual Studio 2013中运行时，“当前路径”是sln所在路径。
而在命令行（cmd）中运行时，“当前路径”是cmd所在路径。
所以命令行（cmd）中，可以用如下两种命令，注意“当前路径”（bin\）和“参数值”（..\）在两种命令中的区别。
E:\MyProjects\IFComicDownloader>bin\IFComicDownloader.exe -a -u http://manhua.dmzj.com/akb49/ -s script\ -c test_cache\
                               |   |                                                             |             |
E:\MyProjects\IFComicDownloader\bin>IFComicDownloader.exe -a -u http://manhua.dmzj.com/akb49/ -s ..\script\ -c ..\test_cache\

