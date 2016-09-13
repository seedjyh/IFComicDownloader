----------------------------------------------------------------------------------------------------
--  IFComicDownload的lua脚本本地测试工具 ver 1.0
--  2016-9-5 13:19:37 by seedjyh@gmail.com
----------------------------------------------------------------------------------------------------
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

-- 加载一个lua文件路径列表里的所有成员
function LoadLuaFileList(lua_file_list)
    for _,v in pairs(lua_file_list) do
        print('loading: ' .. v)
        dofile(v)
    end
end

-- 字符串拆分
function lua_string_split(str, split_char)
    local sub_str_tab = {};
    local i = 0;
    local j = 0;
    while true do
        j = string.find(str, split_char,i+1); -- 从目标串str第i+1个字符开始搜索指定串
        if j == nil then
            table.insert(sub_str_tab,str);
            break;
        end;
        table.insert(sub_str_tab,string.sub(str,i+1,j-1));
        i = j;
    end
    return sub_str_tab;
end

-- 获取一个目录下的所有lua文件的路径列表
function GetAllLuaFilesInPath(path)
    if string.sub(path, string.len(path)) ~= '\\' then
        path = path .. '\\'
    end
    local handle = io.popen("ls " .. path)
    local l = handle:read("*all")
    handle:close()
    local s = lua_string_split(l, '\n')
    
    local result_list = {}
    for _,v in pairs(s) do
        _, end_index = string.find(v, '.lua')
        if end_index == string.len(v) then
            table.insert(result_list, path .. v)
        end
    end
    return result_list
end
