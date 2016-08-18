------------------------------------------------------------
---http://www.huhumh.com/
------------------------------------------------------------
function PictureUrlAnalyse(url)
    local pagestr, err = DownloadURL(url, "", "")
	if type(pagestr) ~= "string" then
		return nil, "DownloadURL " .. url .. " failed\nbecasuse:\n" .. err
	end
	return PicturePageAnalyse(url, pagestr, "")
end

function PicturePageAnalyse(picture_page_url, pagestr, extra_info)
    local result = "<result>"

	if type(picture_page_url) ~= "string" then
		return nil, "error because picture_page_url is not string, but " .. type(picture_page_url)
	end
	
	if type(pagestr) ~= "string" then
		return nil, "error because pagestr is not string, but " .. type(pagestr)
	end

    -- step 1.1: 从URL获取picture_index（从1开始，表示页码）
    local picture_index = GetPageIndexFromURL(picture_page_url)
    if type(picture_index) ~= "number" then
        return nil, "error when trying to get picture index from picture_page_url: " .. picture_page_url
    end
    
    -- step 1.2: 获取file_relative_url_table
    start_index = JumpStr(pagestr, 1, 'PicListUrl = \"', 1)
    if type(start_index) ~= "number" then
        return nil, "Failed to find beginning of PicListUrl."
    end
    
    local PicListUrl = GetStr(pagestr, start_index, "\"")
    if type(PicListUrl) ~= "string" then
        return nil, "Failed to get value of PicListUrl from pagestr"
    end

    local file_relative_url_table = unsuan(PicListUrl , "tazsicoewrn") -- 第二个参数来自http://www.huhumh.com/hh/ai.js
    if type(file_relative_url_table) ~= "table" then
        return nil, "unsuan failed"
    end
    
    -- step 1.3: 获取当前页面的file_relative_url
    local file_relative_url = file_relative_url_table[picture_index]
    if type(file_relative_url) ~= "string" then
        return nil, "No expected file_relative_url for picture_index: " .. tostring(picture_index)
    end

    -- step 2.1: 从URL读取server_index（从1开始，表示服务器编号）
    local start_index = JumpStr(picture_page_url, 1, "s=", 1)
    if type(start_index) ~= "number" then
        return nil, "error when call JumpStr s="
    end
    local server_index = GetStr(picture_page_url, start_index, "*")
    if type(server_index) ~= "string" then
        return nil, "error when trying to read until *"
    end
    server_index = tonumber(server_index)
    if type(server_index) ~= "number" then
        return nil, "error server_index is not number"
    end
    
    -- step 2.2: 读取server_url_list
    local server_url_list = LoadServerList('www.huhumh.com/hh/ai.js')
    
    -- step 2.3：获取当前使用的server_url
    local server_url = server_url_list[server_index - 1]
    if type(server_url) ~= "string" then
        return nil, "No expected server_url for server_index: " .. tostring(server_index)
    end
    
    -- step 3：组装file_url
    local file_url = server_url .. file_relative_url
    
    --------------------------------------------------------------------
    result = result .. "<fileurl>"
    result = result .. file_url
    result = result .. "</fileurl>"
    --------------------------------------------------------------------
    result = result .. "<refererurl>"
    result = result .. picture_page_url
    result = result .. "</refererurl>"
    --------------------------------------------------------------------
    result = result .. "</result>"
    
    return result
end

function GetFileURLFromChapterFun(pagestr)
    -- get chapter id part
    local start_index = JumpStr(pagestr, 1, "var cid=", 1)
    if type(start_index) ~= "number" then
        return nil, "Failed to jump var cid="
    end
    local chapter_id_part = GetStr(pagestr, start_index, ";")
    if type(chapter_id_part) ~= "string" then
        return nil, "Failed to get ChapterID prefix from: " .. pagestr
    end

    -- get key part
    start_index = JumpStr(pagestr, 1, "var key=\\\'", 1)
    if type(start_index) ~= "number" then
        return nil, "Failed to jump var key=\\\'"
    end
    local key_part = GetStr(pagestr, start_index, "\\")
    if type(key_part) ~= "string" then
        return nil, "Failed to get Key from: " .. pagestr
    end

    -- get prefix part
    start_index = JumpStr(pagestr, start_index, "var pix=\"", 1)
    if type(start_index) ~= "number" then
        return nil, "Failed to jump var pix=\""
    end
    local prefix_part = GetStr(pagestr, start_index, "\"")
    if type(prefix_part) ~= "string" then
        return nil, "Failed to get URL prefix from: " .. pagestr
    end

    -- get file part
    start_index = JumpStr(pagestr, start_index, "var pvalue=[\"", 1)
    if type(start_index) ~= "number" then
        return nil, "Failed to jump var pvalue=[\""
    end
    local file_part = GetStr(pagestr, start_index, "\"")
    if type(file_part) ~= "string" then
        return nil, "Failed to get URL picture-part from: " .. pagestr
    end
    
    return prefix_part .. file_part .. "?cid=" .. chapter_id_part .. "&key=" .. key_part
end

function GetPageIndexFromURL(url)
    start_index = JumpStr(url, 1, "v=", 1)
    if type(start_index) ~= "number" then
        return nil, "error when call JumpStr v="
    end
    local picture_index = GetStr(url, start_index, "*")
    if type(picture_index) ~= "string" then
        return nil, "error when trying to read until *"
    end
    picture_index = tonumber(picture_index)
    if type(picture_index) ~= "number" then
        return nil, "error picture_index is not number"
    end
    return picture_index
end

function FindFileUrl(analyse_result)
    local start_index = JumpStr(analyse_result, 1, "<fileurl>", 1)
    if type(start_index) ~= "number" then
        return nil, "error when call JumpStr"
    end

    local file_url = GetStr(analyse_result, start_index, "<")
    if type(file_url) ~= "string" then
        return nil, "error when call GetStr"
    end
    return file_url
end

function FindFileRefererUrl(analyse_result)
    local start_index = JumpStr(analyse_result, 1, "<refererurl>", 1)
    if type(start_index) ~= "number" then
        return nil, "error when call JumpStr"
    end

    local referre_url = GetStr(analyse_result, start_index, "<")
    if type(referre_url) ~= "string" then
        return nil, "error when call GetStr"
    end
    return referre_url
end
