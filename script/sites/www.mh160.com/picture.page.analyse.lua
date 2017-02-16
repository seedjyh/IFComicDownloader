------------------------------------------------------------
---http://www.mh160.com/
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
    local root_url, errmsg = PicturePageAnalyse_GetFileRootURL(pagestr)
    if not root_url then return nil, "PicturePageAnalyse_GetFileURL failed: " .. errmsg end
    
    local pic_index, errmsg = GetPageIndexFromURL(url)
    if not pic_index then return nil, "PicturePageAnalyse_GetFileURL failed: " .. errmsg end
    
    local relative_url, errmsg = PicturePageAnalyse_GetRelativeURLList(pagestr, pic_index)
    if not relative_url then return nil, "PicturePageAnalyse_GetFileURL failed: " .. errmsg end
    return root_url .. relative_url
end

function PicturePageAnalyse_GetFileRootURL(pagestr)
    local start_index = JumpStr(pagestr, 1, "var cid = \"", 1)
    if not start_index then return nil, "PicturePageAnalyse_GetFileRootURL failed: no var cid = \"" end
    local cid_str = GetStr(pagestr, start_index, "\"")
    if not cid_str then return nil, "PicturePageAnalyse_GetFileRootURL failed: no \"" end
    local cid_int = tonumber(cid_str)
    if not cid_int then return "PicturePageAnalyse_GetFileRootURL failed: cid is not number (\"" .. cid_str .. "\"" end

    -- http://www.mh160.com/template/skin4_20110501/js/mh160style/base64.js
    if cid_int > 10000 then
        return "http://img1001.hgysxz.cn"
    else
        return "http://img2002.hgysxz.cn"
    end
end

function GetPageIndexFromURL(url)
    local pos, pos_end = string.find(url, 'p=')
    if not pos then return nil, "GetPageIndexFromURL failed: no \'p=\'" end
    return string.sub(url, pos_end + 1)
end

function PicturePageAnalyse_GetRelativeURLList(pagestr, pic_index)
    local start_index = JumpStr(pagestr, 1, "picTree =\"", 1)
    if not start_index then return nil, "VolumePageAnalyse_GetPictureCount failed: no picTree =\"" end
    local picTree, errmsg = GetStr(pagestr, start_index, "\"")
    if not picTree then return nil, "VolumePageAnalyse_GetPictureCount failed for picTree: no \"" end
    local pic_list_str = from_base64(picTree)
    start_index = JumpStr(pic_list_str, 1, "$qingtiandy$", pic_index - 1)
    return GetStr(pic_list_str, start_index, '$')
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
