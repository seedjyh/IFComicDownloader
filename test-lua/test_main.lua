----------------------------------------------------------------------------------------------------
--  IFComicDownload的lua脚本本地测试工具 ver 1.0
--  2016-9-14 06:03:46 by seedjyh@gmail.com
----------------------------------------------------------------------------------------------------
-- 本文件是测试lua脚本的主文件。
-- 共分4步。
-- 1. 加载script/api/lua脚本，以及script/sites/www.XXX.com/*.lua（具体哪个站点需要指定）脚本。
-- 2. 读取一个指定的html文件（事先用浏览器下载到本地）。
-- 3. 调用想要测试的函数（不止一个，必须先Analyse再Get分析结果）
----------------------------------------------------------------------------------------------------

function PrintLine()
    print("***************************************************************************************")
end

PrintLine()
-- Step 1：加载所有待测试或测试时会用到的lua脚本。
-- Step 1.1：加载测试工具函数
dofile("M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\test_tool.lua")
PrintLine()
-- Step 1.2：加载待测试的脚本
LoadLuaFileList(GetAllLuaFilesInPath("M:\\GitHubRepositories\\IFComicDownloader\\script\\api\\"))
LoadLuaFileList(GetAllLuaFilesInPath("M:\\GitHubRepositories\\IFComicDownloader\\script\\sites\\www.huhumh.com\\"))
PrintLine()
-- Step 1.3：加载table: test_case_list
dofile("M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.huhumh.com\\profile.lua")

PrintLine()
-- Step 2：执行测试
for case_name, case_data in pairs(test_case_list) do
    print('Starting test case: ' .. case_name)
    print('expected:')
    print(ReadFile(case_data.expected_analyse_result))
    print('actual:')
    local analyse_result, errmsg = case_data.function_to_test(case_data.url, ReadFile(case_data.page), "")
    if not analyse_result then
        print("Error! " .. errmsg)
    else
        print(analyse_result)
    end
    print('------------------------------------------------------------------------------------------')
end
PrintLine()

-- END.

-- 注：在Analyse阶段不进行任何转码。
-- 因为转码需要调用C库，而目前并没有开发lua可以离开C程序而调用C库的代码。
-- 转码留在从分析结果Get数据的时候。那部分暂时不测试。
-- 分析结果用肉眼判断。
