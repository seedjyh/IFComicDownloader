【运行方法】
直接双击执行run_test.bat即可。

【设计思想】
一个xml，或者cache文件，定义了map<URL, FilePath>。
开发Lua函数DownloadURL，当被调用时，从上面的映射中找到网页文件，读取并返回。
这样就能在脱离IFComicDownloader.exe的情况下，测试各网站的下载功能。
（注：目前还没开发完成，各网站的profile文件需要改名，比如改成cache.xml；每个网站的文件夹，除了硬盘文件外，应该有自己独立的测试用Lua函数，供总测试main函数调用）
