------------------------------------------------------------
---http://www.dm5.com/
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

    -- step 1: 首先要读取形如http://www.dm5.com/m245859/chapterfun.ashx?cid=245859&page=2&key=&language=1&gtk=6的页面
    -- step 1.1: 读取chapter ID
    local start_index = JumpStr(pagestr, 1, "var DM5_CID=", 1)
    if type(start_index) ~= "number" then
        return nil, "error when call JumpStr var DM5_CID="
    end
    local chapter_id_str = GetStr(pagestr, start_index, ";")
    if type(chapter_id_str) ~= "string" then
        return nil, "error when trying to read DM5_CID until \';\'"
    end

    -- step 1.2: 获取page index
    local picture_index_num, err = GetPageIndexFromURL(picture_page_url)
    if type(picture_index_num) ~= "number" then
        return nil, "error when GetPageIndexFromURL\nbecause:\n" .. err
    end
    
    -- step 1.3: 读取chapterfun
    local chapter_fun_url = GetLongestHost(picture_page_url) .. 'chapterfun.ashx?cid=' .. chapter_id_str .. '&page=' .. tostring(picture_index_num) .. '&key=&language=1&gtk=6'
    local chapter_fun_result_pagestr = DownloadURL(chapter_fun_url, picture_page_url, "") -- 目前是错在这里！
    if type(chapter_fun_result_pagestr) ~= "string" then
        return nil, "Failed to getting 'chapterfun' by URL: " .. chapter_fun_url
    end

    -- step 1.4: 解密chapterfun的返回内容
    local plain_chapter_fun_result, err = eval(chapter_fun_result_pagestr)
    if type(plain_chapter_fun_result) ~= "string" then
        return nil, "Failed to calculate eval to the result of chapterfun, because:\n" .. err
    end
    
    -- step 2: 读取chapterfun的返回内容的明文
    local file_url, err = GetFileURLFromChapterFun(plain_chapter_fun_result)
    if type(file_url) ~= "string" then
        return nil, "Failed to get file URL from plaintext result of chapterfun, because:\n" .. err
    end
    
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
	local index = GetLastPos(url, "g")
	if type(index) ~= "number" then
		return nil, "Can\'t find \'-\' from url " .. url
	end
	local page_index_str = string.sub(url, index + 1, -1)
	if type(page_index_str) ~= "string" then
		return nil, "Can\'t get page-index until the end of url " .. url
	end
	
	local page_index_num = tonumber(page_index_str)
	if type(page_index_num) ~= "number" then
		return nil, "Can\'t tranform page index string \"" .. page_index_str .. "\" to number"
	end
	
	return page_index_num
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
