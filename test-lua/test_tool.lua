----------------------------------------------------------------------------------------------------
--  IFComicDownload的lua脚本本地测试工具 ver 1.0
--  2016-9-5 13:19:37 by seedjyh@gmail.com
----------------------------------------------------------------------------------------------------
-- 这个文件是测试lua脚本的工具函数集合。
-- 共分4步。
-- 1. 加载script/api/lua脚本，以及script/sites/www.XXX.com/*.lua（具体哪个站点需要指定）脚本。
-- 2. 读取一个指定的html文件（事先用浏览器下载到本地）。
-- 3. 调用想要测试的函数（不止一个，必须先Analyse再Get分析结果）。
-- 4. 打印运行结果。
----------------------------------------------------------------------------------------------------
-- step 1
function GetApiScriptList()
    local list = {}
    list[1 + #list] = 'lib.lua'
    list[1 + #list] = 'eval.lua'
    list[1 + #list] = 'site_read.lua'
    return list
end

function GetSiteScriptList()
    local list = {}
    list[1 + #list] = 'comic.page.analyse.lua'
    list[1 + #list] = 'volume.page.analyse.lua'
    list[1 + #list] = 'picture.page.analyse.lua'
    list[1 + #list] = 'url.analyse.lua'
    return list
end

function GetSiteScriptList_extra()
    local list = {}
    return list
end

function AppendPrefixToList(prefix, list)
    local result = {}
    for _,v in pairs(list) do
        result[1 + #result] = prefix .. v
    end
    return result
end

function ConnectTwoList(list_a, list_b)
    local result = {}
    for _,v in pairs(list_a) do
        result[1 + #result] = v
    end
    for _,v in pairs(list_b) do
        result[1 + #result] = v
    end
    return result
end

-- 获取“分析某个网站的页面需要加载的lua文件”列表。
-- 参数：待分析的网站相应分析脚本的文件夹的名字，例如"www.ikanman.com"
-- 返回：一个table，key都是整数，从1开始编号。
-- 使用样例：
-- for _,v in pairs(GetRequiredLuaScriptList('www.ikanman.com')) do
--     print(v)
-- end
function GetRequiredLuaScriptList(site_dir_name)
    local script_root_path = 'M:\\GitHubRepositories\\IFComicDownloader\\script\\'
    local result = {}
    
    result = ConnectTwoList(result, AppendPrefixToList("api\\", GetApiScriptList()))
    result = ConnectTwoList(result, AppendPrefixToList("sites\\" .. site_dir_name .. "\\", ConnectTwoList(GetSiteScriptList(), GetSiteScriptList_extra())))
    return AppendPrefixToList(script_root_path, result)
end

-- 读取一个文件（文件路径从参数file_path传入）并返回文件内容。
-- 返回值：
-- 如果成功，返回文件数据（string格式）
-- 如果出错，第一个返回值是nil，第二个返回值是错误信息（string格式）
function ReadFile(file_path)
    local file, errmsg = io.open(file_path, "rb")
    if not file then return nil, errmsg end
    local data = file:read("*all")
    file:close()
    return data
end
