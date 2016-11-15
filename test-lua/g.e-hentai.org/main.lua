----------------------------------------------------------------------------------------------------
--  IFComicDownload的lua脚本本地测试工具 ver 2.0
--  2016-11-5 12:24:48 by seedjyh@gmail.com
----------------------------------------------------------------------------------------------------
-- 这个文件是对该站点的功能进行测试的主函数（主文件）。直接用dofile执行本文件即可完成测试。
----------------------------------------------------------------------------------
-- 所有和这个网站脚本测试需要（仅和该站有关）的资源都存储在这个路径内。
s_site_path = 'M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\g.e-hentai.org\\'
----------------------------------------------------------------------------------

print('TEST started!')

--  1 - 准备工作
--      1.1 - 加载辅助函数脚本
dofile('M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\test_tool.lua')
--      1.2 - 加载待测试的脚本
--          1.2.1 - api脚本
LoadLuaFileList(GetAllLuaFilesInPath('M:\\GitHubRepositories\\IFComicDownloader\\script\\api\\'))
--          1.2.2 - 站点分析脚本
LoadLuaFileList(GetAllLuaFilesInPath('M:\\GitHubRepositories\\IFComicDownloader\\script\\sites\\g.e-hentai.org\\'))

--  2 - 正式测试
--      2.0 - 加载伪DownloadURL函数。
dofile('M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\g.e-hentai.org\\web\\web.lua')
--      2.1 - 执行待测试的函数
--      Test Case ------------------------------------------------------------------
result, errmsg = ComicUrlAnalyse('http://g.e-hentai.org/g/224263/e06fcdd082/')
if not result then
    print('failed, errmsg is ' .. errmsg)
else
    local expected_result = '<result><comictitle>[Qoopie] Imouto Haramikeshon [English][DesuDesu]</comictitle><volumeinfolist><volumeinfo><volumetitle>gallery</volumetitle><volumeurl>http://g.e-hentai.org/g/224263/e06fcdd082/</volumeurl></volumeinfo></volumeinfolist></result>'
    if expected_result == result then
        print('passed')
    else
        print('FAILED')
        print('expected=' .. expected_result)
        print('actual  =' .. result)
    end
end
--      Test Case ------------------------------------------------------------------
result, errmsg = VolumeUrlAnalyse('http://g.e-hentai.org/g/224263/e06fcdd082/')
if not result then
    print('failed, errmsg is ' .. errmsg)
else
    local expected_result = ''
    if expected_result == result then
        print('passed')
    else
        print('FAILED')
        print('expected=' .. expected_result)
        print('actual  =' .. result)
    end
end
--      Test Case ------------------------------------------------------------------
result, errmsg = ComicUrlAnalyse('http://g.e-hentai.org/g/520477/c799c6aa60/')
if not result then
    print('failed, errmsg is ' .. errmsg)
else
    local expected_result = ''
    if expected_result == result then
        print('passed')
    else
        print('FAILED')
        print('expected=' .. expected_result)
        print('actual  =' .. result)
    end
end
--      Test Case ------------------------------------------------------------------
result, errmsg = VolumeUrlAnalyse('http://g.e-hentai.org/g/520477/c799c6aa60/')
if not result then
    print('failed, errmsg is ' .. errmsg)
else
    local expected_result = ''
    if expected_result == result then
        print('passed')
    else
        print('FAILED')
        print('expected=' .. expected_result)
        print('actual  =' .. result)
    end
end
print('TEST finished!')
