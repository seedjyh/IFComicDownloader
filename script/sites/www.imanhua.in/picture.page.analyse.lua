------------------------------------------------------------
---http://www.imanhua.in
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
    
    local pic_url, errmsg = PicturePageAnalyse_GetRelativeURLList(pagestr, pic_index)
    if not pic_url then return nil, "PicturePageAnalyse_GetFileURL failed: " .. errmsg end
    return "http://images.720rs.com" .. pic_url
end

function GetPageIndexFromURL(url)
    local pos, pos_end = string.find(url, 'p=')
    if not pos then return nil, "GetPageIndexFromURL failed: no \'p=\'" end
    return tonumber(string.sub(url, pos_end + 1))
end

function PicturePageAnalyse_GetRelativeURLList(pagestr, pic_index)
    local start_index = JumpStr(pagestr, 1, "eval(", 1)
    if type(start_index) ~= "number" then
        return nil, "error when looking for eval("
    end

    local eval_str = GetStr(pagestr, start_index, "\n")
    if type(eval_str) ~= "string" then
        return nil, "error when trying to get eval string"
    end

    local eval_str_content, err = JavascriptEval(eval_str)
    if type(eval_str_content) ~= "string" then
        return nil, "error when calculating eval string " .. err
    end
	
	return PicturePageAnalyse_GetRelativeURLFromDeconfusedData(eval_str_content, pic_index);
end

function PicturePageAnalyse_GetRelativeURLFromDeconfusedData(pagestr, pic_index)
    local start_index = JumpStr(pagestr, 1, "\'fs\':", 1)
    if not start_index then return nil, "VolumePageAnalyse_GetPictureCount failed: \'fs\':" end
	if pic_index > 1 then
		start_index = JumpStr(pagestr, start_index, "\',", pic_index - 1)
		if not start_index then return nil, "VolumePageAnalyse_GetPictureCount failed: \'," end
	end
	start_index = JumpStr(pagestr, start_index, "\'", 1)
	if not start_index then return nil, "VolumePageAnalyse_GetPictureCount failed: \'" end
    return GetStr(pagestr, start_index, '\'')
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
