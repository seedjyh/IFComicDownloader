------------------------------------------------------------
---http://www.ikanman.com/
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
    local volume_title, errmsg = VolumePageAnalyse_GetVolumeTitle(pagestr)
    if type(volume_title) ~= "string" then return nil, "Get volume title failed because: " .. errmsg end
    result = result .. "<volumetitle>" .. TransUtf8ToAnsi(volume_title) .. "</volumetitle>"
 
    ----------------------------------------------------------
    result = result .. "<pictureinfolist>"
    -- getting picture count
    local des_info_ciphertext = VolumePageAnalyse_GetCipherText(pagestr)
    if type(des_info_ciphertext) ~= "string" then return nil, function_name .. "failed when getting des ciphertext" end

    local des_info_plaintext = VolumePageAnalyse_decryptDES(des_info_ciphertext)
    if type(des_info_plaintext) ~= "string" then return nil, "Decrypt failed" end
    local info_json = JavascriptEval(des_info_plaintext)

    local picture_count_number = VolumePageAnalyse_GetPictureCountFromInfo(info_json)
    if type(picture_count_number) ~= "number" then
        return nil, function_name .. "failed when getting picture count"
    end

    local now_start = 1
    local index = 1
    local picture_url_root = volume_page_url
    while index <= picture_count_number do
        local picture_url = picture_url_root .. "#p=" .. tostring(index)
        result = result .. "<pictureinfo><pictureurl>" .. picture_url .. "</pictureurl></pictureinfo>"
	    index = index + 1
    end

    ----------------------------------------------------------
    result = result .. "</pictureinfolist>"
    ----------------------------------------------------------------------------
    result = result .. "</result>"

    return result
end

function VolumePageAnalyse_GetVolumeTitle(pagestr)
    local start_index = JumpStr(pagestr, 1, "<h2>", 1);
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping <h2>"
    end
    local volume_title = GetStr(pagestr, start_index, "<")
    if type(volume_title) ~= "string" then
        return nil, function_name .. "failed when getting volume title"
    end
    return volume_title
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
