----------------------------------------------------------------------------------------------------
--  IFComicDownload的lua脚本本地测试工具 ver 1.0
--  2016-9-5 13:19:37 by seedjyh@gmail.com
----------------------------------------------------------------------------------------------------
-- 这个文件是测试lua脚本的主文件。
-- 共分4步。
-- 1. 加载script/api/lua脚本，以及script/sites/www.XXX.com/*.lua（具体哪个站点需要指定）脚本。
-- 2. 读取一个指定的html文件（事先用浏览器下载到本地）。
-- 3. 调用想要测试的函数（不止一个，必须先Analyse再Get分析结果）
----------------------------------------------------------------------------------------------------
dofile("M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\test_tool.lua")

------------------------------------------------------------------
-- 预测参数
-- 待测试的网站目录名（位于script/sites/下），例如'www.ikanman.com'
local site_dir = 'www.dm5.com'
-- 待分析的网页文件名（已经被下载到本地硬盘）
local web_file_path = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\comic_page.html"
-- 待分析的网页URL
local web_page_url = "http://g.e-hentai.org/s/5ea57e66ac/523011-1"
------------------------------------------------------------------

-- Step 1：加载所有待测试或测试时会用到的lua脚本。
for _,v in pairs(GetRequiredLuaScriptList(site_dir)) do
    dofile(v)
end

-- Step 2：加载待测试的网页文件。
pagestr = ReadFile(web_file_path)

-- Step 3：调用欲测试的函数。
--print(GetPageIndexFromURL(web_page_url))
print(ComicPageAnalyse(web_page_url, pagestr, ""))

-- END.

-- 注：在Analyse阶段不进行任何转码。
-- 因为转码需要调用C库，而目前并没有开发lua可以离开C程序而调用C库的代码。
-- 转码留在从分析结果Get数据的时候。那部分暂时不测试。
-- 分析结果用肉眼判断。
