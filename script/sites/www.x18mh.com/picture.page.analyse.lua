------------------------------------------------------------
---http://www.x18mh.com
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
    --------------------------------------------------------------------
    result = result .. "<fileurl>"
    local file_url, errmsg = PicturePageAnalyse_GetFileURL(picture_page_url, pagestr)
    if not file_url then return nil, "PicturePageAnalyse failed: " .. errmsg end
    result = result .. TransUtf8ToAnsi(file_url)
    result = result .. "</fileurl>"
    --------------------------------------------------------------------
    result = result .. "<refererurl>"
    result = result .. picture_page_url
    result = result .. "</refererurl>"
    --------------------------------------------------------------------
    result = result .. "</result>"
    
    return result
end

function PicturePageAnalyse_GetFileURL(url, pagestr)
    local pic_index, errmsg = GetPageIndexFromURL(url)
    if not pic_index then return nil, "PicturePageAnalyse_GetFileURL failed: " .. errmsg end
    
    local pic_url, errmsg = PicturePageAnalyse_GetPicURL(pagestr, pic_index)
    if not pic_url then return nil, "PicturePageAnalyse_GetFileURL failed: " .. errmsg end
    return pic_url
end

function GetPageIndexFromURL(url)
    local pos, pos_end = string.find(url, 'p=')
    if not pos then return nil, "GetPageIndexFromURL failed: no \'p=\'" end
    return tonumber(string.sub(url, pos_end + 1))
end

function PicturePageAnalyse_GetPicURL(pagestr, pic_index)
	local start_index = JumpStr(pagestr, 1, "var qTcms_S_m_murl_e=\"", 1)
    if type(start_index) ~= "number" then
        return nil, "error when looking for var qTcms_S_m_murl_e=\""
    end
    local base64_str = GetStr(pagestr, start_index, "\"")
    if type(base64_str) ~= "string" then
        return nil, "error when trying to get end of str"
    end
	image_url_list = from_base64(base64_str)
    if type(image_url_list) ~= "string" then
        return nil, "error when decode base64 string " .. err
    end

    local start_index = 1
	if pic_index > 1 then
		start_index = JumpStr(image_url_list, 1, "$qingtiandy$", pic_index - 1)
	end
	
	pic_url = GetStr(image_url_list, start_index, "$")
	if type(pic_url) ~= "string" then
		return nil, "no pic_url"
	end
	return pic_url
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
	return (string.len(data) >= 0)
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
