调试时要注意的点：
在Visual Studio 2013中运行时，“当前路径”是sln所在路径。
而在命令行（cmd）中运行时，“当前路径”是cmd所在路径。
所以命令行（cmd）中，可以用如下两种命令，注意“当前路径”（bin\）和“参数值”（..\）在两种命令中的区别。
E:\MyProjects\IFComicDownloader>bin\IFComicDownloader.exe -a -u http://manhua.dmzj.com/akb49/ -s script\ -c test_cache\
                               |   |                                                             |             |
E:\MyProjects\IFComicDownloader\bin>IFComicDownloader.exe -a -u http://manhua.dmzj.com/akb49/ -s ..\script\ -c ..\test_cache\

