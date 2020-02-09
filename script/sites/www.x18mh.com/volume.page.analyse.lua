------------------------------------------------------------
---http://www.x18mh.com
------------------------------------------------------------
function VolumeUrlAnalyse(url)
    local pagestr, err = DownloadURL(url, "", "")
	if type(pagestr) ~= "string" then
		return nil, "DownloadURL " .. url .. " failed\nbecasuse:\n" .. err
	end
	return VolumePageAnalyse(url, pagestr, "")
end

function VolumePageAnalyse(volume_page_url, pagestr, extra_info)
    local function_name = "VolumePageAnalyse(\"" .. volume_page_url .."\")"
    local result = "<result>"
    ----------------------------------------------------------------------------
    local title, errmsg = VolumePageAnalyse_GetVolumeTitle(pagestr)
    if not title then return nil, "VolumePageAnalyse failed: " .. errmsg end
    result = result .. "<volumetitle>" .. title .. "</volumetitle>"
    ----------------------------------------------------------   
    result = result .. "<pictureinfolist>"
    local pic_count, errmsg = VolumePageAnalyse_GetPictureCount(pagestr)
	if type(pic_count) ~= "number" then return nil, "Get picture count from volume page failed, because: " .. errmsg end
    for i = 1, pic_count, 1 do
        pic_url = volume_page_url .. "?p=" .. tostring(i)
        result = result .. "<pictureinfo><pictureurl>" .. pic_url .. "</pictureurl></pictureinfo>"
    end
    result = result .. "</pictureinfolist>"
    ----------------------------------------------------------------------------
    result = result .. "</result>"
    return result
end

function VolumePageAnalyse_GetVolumeTitle(pagestr)
    local start_index = JumpStr(pagestr, 1, "<h2>", 1)
    if not start_index then return nil, "VolumePageAnalyse_GetVolumeTitle failed: no <h2>" end
    local title, errmsg = GetStr(pagestr, start_index, "\"")
    if not title then return nil, "VolumePageAnalyse_GetVolumeTitle for title failed: no <" end
    return TransUtf8ToAnsi(title)
end

function VolumePageAnalyse_GetPictureCount(pagestr)
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
	
	return VolumePageAnalyse_GetPictureCountFromBase64DecodeResult(image_url_list)
end

function VolumePageAnalyse_GetPictureCountFromBase64DecodeResult(str)
	local count = 1
    local start_index = 1
	while true do
		now_index = JumpStr(str, start_index, "$qingtiandy$", 1)
		if type(now_index) ~= "number" then
			break
		end
		start_index = now_index
		count = count + 1
	end
	return count
end

function VolumePageGetVolumeTitle(analyse_result)
    local result_end_index=JumpStr(analyse_result, 1, "<volumetitle>", 1)
    if type(result_end_index) ~= "number" then
        return nil
    end

    return GetStr(analyse_result, result_end_index, "<")
end

function VolumePageGetPictureCount(analyse_result)
    local volume_info_count = 0
    local start_index = JumpStr(analyse_result, 1, "<pictureinfolist>", 1)
    if type(start_index) ~= "number" then
        return nil
    end

    local now_start_index = start_index
    while true do
        now_start_index = JumpStr(analyse_result, now_start_index, "<pictureinfo>", 1)
        if type(now_start_index) ~= "number" then
            break
        end
        volume_info_count = volume_info_count + 1
    end
    return volume_info_count
end

function VolumePageGetPictureURL(analyse_result, index) -- index starts from 1
    if index <= 0 then
        return nil, "Invalid index: " .. tostring(index)
    end
    local start_index = JumpStr(analyse_result, 1, "<pictureinfolist>", 1)
    if type(start_index) ~= "number" then
        return nil, "Getting <pictureinfolist> failed"
    end

    start_index = JumpStr(analyse_result, start_index, "<pictureurl>", index)
    if type(start_index) ~= "number" then
        return nil, "Jumping " .. tostring(index) .. " <pictureurl> failed"
    end

    return GetStr(analyse_result, start_index, "<")
end

function VolumePageGetPictureCookie(analyse_result, index)
    return ""
end

function VolumePageFindExtraInfo(analyse_result)
    return analyse_result
end
