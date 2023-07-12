function VolumeUrlAnalyse(url)
    local pagestr, err = DownloadURL(url, "", "")
	if type(pagestr) ~= "string" then
		return nil, "DownloadURL " .. url .. " failed\nbecasuse " .. err
	end
	return VolumePageAnalyse(url, pagestr, "")
end

function VolumePageAnalyse(volume_page_url, pagestr, extra_info)
    local function_name = "VolumePageAnalyse(\"" .. volume_page_url .."\")"
    local result = "<result>"
    ----------------------------------------------------------------------------
    -- getting volume title
    local start_index = JumpStr(pagestr, 1, "<span class=\"last\">", 1);
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping <span class=\"last\">"
    end
    local volume_title = GetStr(pagestr, start_index, "<")
    if type(volume_title) ~= "string" then
        return nil, function_name .. "failed when getting volume title"
    end
    
    result = result .. "<volumetitle>" .. volume_title .. "</volumetitle>"
 
    ----------------------------------------------------------   
    result = result .. "<pictureinfolist>"

    -- start
    start_index = 1
    local page_index = 0
    while true do
        page_index = page_index + 1
        start_index = JumpStr(pagestr, start_index, "<img decoding=\"async\" src=\"", 1)
        if type(start_index) ~= "number" then
            break
        end
        local picture_url = GetStr(pagestr, start_index, "\"")
        if type(picture_url) ~= "string" then
            break
        end
        result = result .. "<pictureinfo><pictureurl>" .. volume_page_url .. "#" .. tostring(page_index) .. "</pictureurl></pictureinfo>"
    end

    ----------------------------------------------------------
    result = result .. "</pictureinfolist>"
    ----------------------------------------------------------------------------
    result = result .. "</result>"

    return result
end

function VolumePageGetVolumeTitle(analyse_result)
    local result_end_index=JumpStr(analyse_result, 1, "<volumetitle>", 1)
    if type(result_end_index) ~= "number" then
        return nil
    end

    return TransUtf8ToAnsi(GetStr(analyse_result, result_end_index, "<"))
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
