------------------------------------------------------------
---http://g.e-hentai.org/
------------------------------------------------------------
function VolumeUrlAnalyse(url)
    local pagestr, err = DownloadURL(url, "", "")
	if type(pagestr) ~= "string" then
		return nil, "DownloadURL " .. url .. " failed\nbecasuse:\n" .. err
	end
	return VolumePageAnalyse(url, pagestr, "")
end

function VolumePageAnalyse(url, pagestr, extra_info)
    local function_name = "VolumePageAnalyse(\"" .. url .."\")"
    local result = "<result>"
    ----------------------------------------------------------------------------
    -- getting volume title
    result = result .. "<volumetitle>gallery</volumetitle>"
    ----------------------------------------------------------
    result = result .. "<pictureinfolist>"

    -- getting sub_volume_url_list
    local sub_volume_url_list = GetSubVolumeUrlList(pagestr)

    -- handle each sub-volume URL in sub_volume_url_list
    for i = 1, #sub_volume_url_list do
        pic_url_list_for_subvolume, errmsg = SubVolumePageAnalyse(sub_volume_url_list[i])
        if not pic_url_list_for_subvolume then
            return nil, errmsg
        end
        for i = 1, #pic_url_list_for_subvolume do
            result = result .. "<pictureinfo><pictureurl>" .. pic_url_list_for_subvolume[i] .. "</pictureurl></pictureinfo>"
        end
    end
    ----------------------------------------------------------
    result = result .. "</pictureinfolist>"
    ----------------------------------------------------------------------------
    result = result .. "</result>"

    return result
end

-- 从首个VolumePage分析出所有SubVolumePage的URL。
function GetSubVolumeUrlList(pagestr)
    local start_index = JumpStr(pagestr, 1, "ptt", 1)
    if not start_index then return nil, "No ptt" end
    
    local end_index = JumpStr(pagestr, start_index, "</tr>", 1)
    if not start_index then return nil, "No </tr>" end

    local result = {}
    while true do
        start_index = JumpStr(pagestr, start_index, "href=\"", 1)
        if not start_index or start_index > end_index then
            break
        end
        local now_url = GetStr(pagestr, start_index, "\"")
        if not now_url then return nil, "Failed to get now_url" end
        
        -- 判重：如果这个SubVolumeURL就是table中的第2个URL，可以认为这个SubVolumeURL是“下一页”，因此跳过。
        if result[1] ~= now_url then
            table.insert(result, now_url)
        end
    end
    return result
end

-- 仅仅分析一个SubVolume，返回该SubVolumePage的所有PicturePageURL的list（table, key starts from 1）
function SubVolumePageAnalyse(url)
    local pagestr, errmsg = DownloadURL(url, "", "")
    if not pagestr then
        return nil, "DownloadURL failed(url=" .. url .. ')'
    end
    
    local pic_url_list = {}
    local start_index = 1
    while true do
        start_index = JumpStr(pagestr, start_index, "\"gdtm\"", 1)
        if type(start_index) ~= "number" then break end
        start_index = JumpStr(pagestr, start_index, "<a href=\"", 1)
        if type(start_index) ~= "number" then return nil, "getting picture url failed" end
        local picture_url = GetStr(pagestr, start_index, "\"")
        if type(picture_url) ~= "string" then return nil, "getting picture url failed" end
        table.insert(pic_url_list, picture_url)
    end
    return pic_url_list
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
