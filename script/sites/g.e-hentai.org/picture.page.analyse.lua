------------------------------------------------------------
---http://g.e-hentai.org/
------------------------------------------------------------
-- 对外接口
function PictureUrlAnalyse(url)
    local pagestr, err = DownloadURL(url, "", "")
	if type(pagestr) ~= "string" then
		return nil, "DownloadURL " .. url .. " failed\nbecasuse:\n" .. err
	end
	return PicturePageAnalyse(url, pagestr, "")
end

-- 内部
function PicturePageAnalyse(picture_page_url, pagestr, extra_info)
    local result = "<result>"

	if type(picture_page_url) ~= "string" then
		return nil, "error because picture_page_url is not string, but " .. type(picture_page_url)
	end
	
	if type(pagestr) ~= "string" then
		return nil, "error because pagestr is not string, but " .. type(pagestr)
	end

    --------------------------------------------------------------------
    -- Getting image file url
    local start_index = JumpStr(pagestr, 1, "id=\"img\"", 1)
    if type(start_index) ~= "number" then return nil, "Failed when jumping id=\"img\" to get image file URL." end
    start_index = JumpStr(pagestr, start_index, "src=\"", 1)
    if type(start_index) ~= "number" then return nil, "Failed when jumping src=\" to get image file URL." end
    local image_file_url = GetStr(pagestr, start_index, "\"")
    if type(image_file_url) ~= "string" then return nil, "Failed when getting image file URL until \"" end
    --------------------------------------------------------------------
    result = result .. "<fileurl>"
    result = result .. image_file_url
    result = result .. "</fileurl>"
    --------------------------------------------------------------------
    result = result .. "<refererurl>"
    result = result .. picture_page_url
    result = result .. "</refererurl>"
    --------------------------------------------------------------------
    result = result .. "</result>"
    
    return result
end

-- 对外接口
function GetPageIndexFromURL(url)
    local start_index = JumpStr(url, 1, '-', 2)
    if type(start_index) ~= "number" then return nil, 'No minus sign in url' end
    local pic_index_str = GetStr(url, start_index, '')
    if type(pic_index_str) ~= "string" then return nil, "No index in url" end
    local pic_index = tonumber(pic_index_str)
    if type(pic_index) ~= "number" then return nil, "String after minus sign (" .. pic_index_str .. ") is not a number" end
    return pic_index
end

-- 对外接口
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

-- 对外接口
-- 参数：图片文件数据
function CheckImageFileValidity(data)
	print('enter: CheckImageFileValidity, size=' .. string.len(data))
	return (string.len(data) >= 128)
end

-- 内部
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
