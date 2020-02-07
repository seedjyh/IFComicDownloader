function PictureUrlAnalyse(url)
    local pagestr, err = DownloadURL(url, "", "")
	if type(pagestr) ~= "string" then
		return nil, "DownloadURL " .. url .. " failed\nbecasuse " .. err
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
    
    local picture_index_num, err = GetPageIndexFromURL(picture_page_url)
    if type(picture_index_num) ~= "number" then
        return nil, "error when GetPageIndexFromURL\nbecause: " .. err
    end

	-- chapter path
	start_index = JumpStr(pagestr, 1, "var chapterPath = \"", 1)
	chapter_path = GetStr(pagestr, start_index, "\"")
	if type(chapter_path) ~= "string" then
        return nil, "error when getting chapterPath"
    end

	-- chapterImages
    start_index = JumpStr(pagestr, 1, "var chapterImages = [", 1)
    if type(start_index) ~= "number" then
        return nil, "error when looking for var chapterImages = ["
    end
    local chapter_images = GetStr(pagestr, start_index, "]", 1)
    if type(chapter_images) ~= "string" then
        return nil, "error when trying to get chapter images"
    end
	
	-- KEY CODE HERE!
	local url_start_index = JumpStr(chapter_images, 1, "\"", (picture_index_num - 1) * 2 + 1)
	local relative_url = GetStr(chapter_images, url_start_index, "\"")
	local file_url = "https://img001.1fi4b.cn/" .. chapter_path .. relative_url
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

function GetPageIndexFromURL(url)
	local index = JumpStr(url, 1, "=", 1)
	if type(index) ~= "number" then
		return nil, "Can\'t find \'=\' from url " .. url
	end
	local page_index_str = string.sub(url, index)
	if type(page_index_str) ~= "string" then
		return nil, "Can\'t get page-index until \'\' in url " .. url
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

-- 对外接口
-- 参数：图片文件数据
function CheckImageFileValidity(data)
	print('enter: CheckImageFileValidity')
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
