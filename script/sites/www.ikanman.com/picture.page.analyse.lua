------------------------------------------------------------
---http://www.ikanman.com/
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

    --------------------------------------------------------------------
    -- picture index
    local pic_index = GetPageIndexFromURL(picture_page_url)
    if type(pic_index) ~= "number" then return nil, "GetPageIndexFromURL failed" end
    --------------------------------------------------------------------
	local info_json = ""
    local des_info_ciphertext, err = VolumePageAnalyse_GetDesCipherText(pagestr)
	local pic_file_host = ""
    if type(des_info_ciphertext) ~= "string" then
		-- just eval p.a.c.k.e.d
		local eval_str, err = VolumePageAnalyse_GetEvalStr(pagestr)
		if type(eval_str) ~= "string" then return nil, "Get Eval Str failed." end
		info_json = MyJavascriptEval(eval_str)
		pic_file_host = 'http://i.yogajx.com'
	else
		print('There\'s DES cipher to handle')
		local des_info_plaintext = VolumePageAnalyse_decryptDES(des_info_ciphertext)
		if type(des_info_plaintext) ~= "string" then return nil, "Decrypt failed" end
		info_json = JavascriptEval(des_info_plaintext)
		pic_file_host = 'http://idx0.hamreus.com:8080'
	end
    
    local file_relative_url = VolumePageAnalyse_GetFileURL(info_json, pic_index)
    if type(file_relative_url) ~= "string" then
        return nil, "failed when getting file url from ciphertext(json)"
    end
    
    local file_relative_path = VolumePageAnalyse_GetFilePath(info_json)
    if type(file_relative_path) ~= "string" then
        return nil, "failed when getting file relative path from ciphertext(json)"
    end
    --------------------------------------------------------------------
    local file_url = pic_file_host .. file_relative_path .. file_relative_url
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
    local start_index = JumpStr(url, 1, '=', 1)
    if type(start_index) ~= "number" then return nil, 'No equal sign in url' end
    local pic_index_str = GetStr(url, start_index, '.')
    if type(pic_index_str) ~= "string" then return nil, "No index in url" end
    local pic_index = tonumber(pic_index_str)
    if type(pic_index) ~= "number" then return nil, "Not a number after equal sign in url" end
    return pic_index
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
	return (string.len(data) >= 100) and (data[0] ~= '<')
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
