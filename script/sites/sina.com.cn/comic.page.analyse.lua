------------------------------------------------------------
---slide.sports.sina.com.cn
------------------------------------------------------------
function ComicUrlAnalyse(url)
    local sharp_index = JumpStr(url, 1, '#', 1)
    if type(sharp_index) == "number" then
        url = string.sub(url, 1, sharp_index)
    end
    local pagestr, err = DownloadURL(url, "", "")
	if type(pagestr) ~= "string" then
		return nil, "DownloadURL " .. url .. " failed\nbecasuse " .. err
	end
	return ComicPageAnalyse(url, pagestr, "")
end

function ComicPageAnalyse(comic_page_url, pagestr, extra_info)
    local result = "<result>"

    ----------------------------------------------------------------------------
    result = result .. "<comictitle>"
    ----------------------------------------------------------
    local result_end_index=JumpStr(pagestr, 1, "<dt>", 1)
    if type(result_end_index) ~= "number" then
        return nil, "JumpStr <dt> failed"
    end

    local comic_title = GetStr(pagestr, result_end_index, "<")
    if type(comic_title) ~= "string" then
        return nil, "GetStr until < failed"
    end
    result = result .. comic_title
    ----------------------------------------------------------
    result = result .. "</comictitle>"
    ----------------------------------------------------------------------------
    

    ----------------------------------------------------------------------------
    result = result .. "<volumeinfolist>"
    ----------------------------------------------------------

    result = result .. "<volumeinfo>"
    result = result .. "<volumetitle>gallery</volumetitle>"
    result = result .. "<volumeurl>" .. comic_page_url .. "</volumeurl>"
    result = result .. "</volumeinfo>"

    ----------------------------------------------------------
    result = result .. "</volumeinfolist>"
    ----------------------------------------------------------------------------
    result = result .. "</result>"

    return result
end

function ComicPageGetComicTitle(analyse_result)
    local result_end_index=JumpStr(analyse_result, 1, "<comictitle>", 1)
    if type(result_end_index) ~= "number" then
        return nil
    end

    return GetStr(analyse_result, result_end_index, "<")
end

function ComicPageGetVolumeCount(analyse_result)
	local start_index = JumpStr(analyse_result, 1, "<volumeinfolist>",  1)
	local end_index   = JumpStr(analyse_result, 1, "</volumeinfolist>", 1)
	local volume_count = 0
	local temp_start_index = start_index

	while temp_start_index < end_index do
	    local temp_end_index = JumpStr(analyse_result, temp_start_index, "<volumeinfo>", 1)
	    if type(temp_end_index) ~= "number" then
	        break
	    end
	    volume_count = volume_count + 1
	    temp_start_index = temp_end_index + string.len("<volumeinfo>")
	end

	return volume_count
end

function ComicPageGetVolumeTitle(analyse_result, index)	
	local start_index = JumpStr(analyse_result, 1, "<volumeinfolist>",  1)
	local temp_start_index = start_index
	for i = 1, index do
	    local temp_end_index = JumpStr(analyse_result, temp_start_index, "<volumeinfo>", 1)
	    if type(temp_end_index) ~= "number" then
	        return nil, "No enough <volumeinfo>"
	    end
	    temp_start_index = temp_end_index
	end

	temp_start_index = JumpStr(analyse_result, temp_start_index, "<volumetitle>", 1)

	if type(temp_start_index) ~= "number" then
	    return nil, "Can\'t find <volumetitle>"
	end
	return GetStr(analyse_result, temp_start_index, "<")
end

function ComicPageGetVolumeURL(analyse_result, index)
	local start_index = JumpStr(analyse_result, 1, "<volumeinfolist>",  1)
	local temp_start_index = start_index
	for i = 1, index do
	    local temp_end_index = JumpStr(analyse_result, temp_start_index, "<volumeinfo>", 1)
	    if type(temp_end_index) ~= "number" then
	        return nil, "No enough <volumeinfo>"
	    end
	    temp_start_index = temp_end_index
	end

	temp_start_index = JumpStr(analyse_result, temp_start_index, "<volumeurl>", 1)

	if type(temp_start_index) ~= "number" then
	    return nil, "Can\'t find <volumeurl>"
	end
	return GetStr(analyse_result, temp_start_index, "<")
end

function ComicPageFindExtraInfo(analyse_result)
    return analyse_result
end
