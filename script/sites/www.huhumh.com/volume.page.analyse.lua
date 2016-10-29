------------------------------------------------------------
---http://www.huhumh.com/
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
    
    volume_title, errmsg = GetVolumeTitle(pagestr)
    if volume_title == nil then
        return nil, function_name .. "failed because: " .. errmsg
    end
    result = result .. "<volumetitle>" .. volume_title .. "</volumetitle>"
 
    ----------------------------------------------------------   
    result = result .. "<pictureinfolist>"
    local picture_count_number, errmsg = GetPictureCount(pagestr)
    if not picture_count_number then
        return nil, "failed in getting picture count because: " .. errmsg
    end
    
    for index = 1,picture_count_number do
        result = result .. "<pictureinfo><pictureurl>" .. GeneratePictureURL(volume_page_url, index) .. "</pictureurl></pictureinfo>"
	    index = index + 1
    end

    ----------------------------------------------------------
    result = result .. "</pictureinfolist>"
    ----------------------------------------------------------------------------
    result = result .. "</result>"

    return result
end

function GetVolumeTitle(pagestr)
    local function_name = "GetVolumeTitle(pagestr)"
    local start_index = JumpStr(pagestr, 1, "<head><title>", 1);
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping class=b>"
    end
    
    local now_title = GetStr(pagestr, start_index, "<")
    if type(now_title) ~= "string" then
        return nil, function_name .. "failed when getting now_title until <"
    end
    
    now_title = string.match(now_title, "%s*(.-)%s*$")
    now_title = string.sub(now_title, 1, -16)
    return TransUtf8ToAnsi(now_title)
end

function GetPictureCount(pagestr)
    local start_index = JumpStr(pagestr, 1, "hdPageCount", 1)
    if not start_index then return nil, "No hdPageCount" end
    start_index = JumpStr(pagestr, start_index, "value=\"", 1)
    if not start_index then return nil, "value=\"" end
    local count_str = GetStr(pagestr, start_index, "\"")
    if not count_str then return "Failed when getting string until \"" end
    return tonumber(count_str)
end

function GeneratePictureURL(volume_page_url, pic_index)
    -- volume_page_url sample: http://www.huhumh.com/hu243964/1.html?s=11
    -- pic_index starts from 1
    local last_slash_index, _ = GetLastPos(volume_page_url, '/')
    local url_start_part = string.sub(volume_page_url, 0, last_slash_index)
    local question_mark_index = GetLastPos(volume_page_url, '?')
    local url_last_part = string.sub(volume_page_url, question_mark_index)
    return url_start_part .. tostring(pic_index) .. ".html" .. url_last_part
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
