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
    -- getting volume title
    local start_index = JumpStr(pagestr, 1, "class=b>", 1);
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping class=b>"
    end
    
    start_index = JumpStr(pagestr, start_index, ">", 1)
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping >"
    end
    
    local volume_title = GetStr(pagestr, start_index, "<")
    if type(volume_title) ~= "string" then
        return nil, function_name .. "failed when getting volume title"
    end
    
    result = result .. "<volumetitle>" .. volume_title .. "</volumetitle>"
 
    ----------------------------------------------------------   
    result = result .. "<pictureinfolist>"
    -- getting picture count
    local pic_url_table = GetPicUrlTableFromVolumePage(pagestr)
    local picture_count_number = #pic_url_table
    
    for index = 1,picture_count_number do
        local picture_url = volume_page_url .. "*v=" .. tostring(index)
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
