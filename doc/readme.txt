编译方式：
使用Visual Studio 2013。
本项目目前有两种编译模式：
Debug模式生成可用的程序exe，使用lua、libcurl、gzip库，编译时需要它们的lib，运行时需要它们的dll。
DebugGoogleTest模式是单元测试模式，除了上述的库之外，还使用googletest库。

需要发布的文件：
bin目录和script目录下所有git受控的文件。所需的dll已经放在bin目录下了。

使用方式：
执行IFComicDownloader.exe，用-u指定待下载漫画的URL。
例如E:\test\bin\IFComicDownloader.exe -u http://www.dm5.com/manhua-platinum-end/
另外，-s用于指定script目录，-c用于指定cache目录。如果不指定，那么这两个目录都和bin目录、script目录同级。
