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
    local start_index = JumpStr(pagestr, 1, "var g_chapter_name = \"", 1);
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping var g_chapter_name = \""
    end
    local volume_title = GetStr(pagestr, start_index, "\"")
    if type(volume_title) ~= "string" then
        return nil, function_name .. "failed when getting volume title"
    end
    
    result = result .. "<volumetitle>" .. volume_title .. "</volumetitle>"
 
    ----------------------------------------------------------   
    result = result .. "<pictureinfolist>"
    -- getting picture count
    start_index = JumpStr(pagestr, 1, "var g_max_pic_count = ", 1);
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping var g_max_pic_count = "
    end
    local picture_count_str = GetStr(pagestr, start_index, ";")
    if type(volume_title) ~= "string" then
        return nil, function_name .. "failed when getting picture count"
    end
    local picture_count_number = tonumber(picture_count_str)
    if type(picture_count_number) ~= "number" then
        return nil, function_name .. "failed when transforming picture count from string " .. picture_count_str .. " to number"
    end

    local now_start = 1
    local index = 1
    local picture_url_root = CutTailAfterLastKey(volume_page_url, ".")
    picture_url_root = string.sub(picture_url_root, 1, string.len(picture_url_root) - string.len("."))
    while index <= picture_count_number do
        local picture_url = picture_url_root .. "-" .. tostring(index) .. ".shtml"
        result = result .. "<pictureinfo><pictureurl>" .. picture_url .. "</pictureurl></pictureinfo>"
	    index = index + 1
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
