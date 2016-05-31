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
    result = result .. "<volumetitle>gallery</volumetitle>"
 
    ----------------------------------------------------------   
    result = result .. "<pictureinfolist>"
    -- getting picture count
    local start_index = JumpStr(pagestr, 1, "<div class=\"picmidmid\">", 1);
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping <div class=\"picmidmid\">"
    end
    
    local end_index = JumpStr(pagestr, start_index, "<div class=\"picmidright\">", 1)
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping <div class=\"picmidright\">"
    end

    local pic_index = 1
    while true do
        start_index = JumpStr(pagestr, start_index, "bigimg=\"", 1)
        if type(start_index) ~= "number" then
            break
        end
        if start_index > end_index then
            break
        end
        local picture_url = GetStr(pagestr, start_index, "\"")
        result = result .. "<pictureinfo><pictureurl>" .. volume_page_url .. "&" .. pic_index .. "</pictureurl></pictureinfo>"
        -- 在这里，故意连续重复VolumeURL，重复次数和图片数相同，从而暗示图片数。
        -- 用额外的&+数字，来为PictureURL暗示图片序号。但是，下载时如果带上图片序号就无法打开网页了，因此要在得到图片序号后去掉'&'及之后的内容。
        pic_index = pic_index + 1
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
