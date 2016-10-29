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

    -- step 1: 获取隐含图片文件URL的字符串
    local start_index = JumpStr(pagestr, 1, "<img id=", 1)
    if not start_index then return nil, "Failed in getting <img id=" end
    
    start_index = JumpStr(pagestr, start_index, "name=\"", 1)
    if not start_index then return nil, "Failed in jumping name=\"" end

    local ciphertext = GetStr(pagestr, start_index, "\"")
    if not ciphertext then return nil, "Failed in getting ciphertext(with file URL) until \"" end
    
    local file_relative_url = unsuan(ciphertext)
    if not file_relative_url then return nil, "unsuan failed" end
    
    -- step 2: 获取服务器地址
    local server_url_table, errmsg = GetServerURLTable(pagestr)
    if not server_url_table then return nil, "Getting server url table failed because: " .. errmsg end

    -- 从代码看似乎会有从pic-page-url的参数d获取服务器index的可能。不过没找到样例，暂时不管。
    -- 注意server_url_table下标从1开始，而网页中的相应表的下标从0开始。
    local file_url = server_url_table[1] .. file_relative_url
    
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

function GetServerURLTable(pagestr)
    local start_index = JumpStr(pagestr, 1, "hdDomain", 1)
    if not start_index then return nil, "Jumping hdDomain failed" end
    local start_index = JumpStr(pagestr, start_index, "value=\"", 1)
    if not start_index then return nil, "Jumping value=\" failed" end
    local server_url_str = GetStr(pagestr, start_index, "\"")
    if not server_url_str then return nil, "Getting server url str until \" failed" end
    return StringSplit(server_url_str, '|')
end

-- 此函数会被IFComicDownloader调用，不可忽略。
function GetPageIndexFromURL(url)
    local start_index = GetLastPos(url, "/")
    local page_index_str =  GetStr(url, start_index + 1, ".")
    if not page_index_str then return "Getting page_index_str until . failed" end
    return tonumber(page_index_str)
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
