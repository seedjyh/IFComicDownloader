------------------------------------------------------------
---http://www.2manhua.com
------------------------------------------------------------
function ComicUrlAnalyse(url)
    local pagestr, err = DownloadURL(url, "", "")
	if type(pagestr) ~= "string" then
		return nil, "DownloadURL " .. url .. " failed\nbecasuse:\n" .. err
	end
	return ComicPageAnalyse(url, pagestr, "")
end

function ComicPageAnalyse(comic_page_url, pagestr, extra_info)
    local result = "<result>"

    ----------------------------------------------------------------------------
    result = result .. "<comictitle>"
    local comic_title, errmsg = ComicPageAnalyse_GetComicTitle(pagestr)
    if not comic_title then return nil, "ComicPageAnalyse failed because: " .. errmsg end
    result = result .. comic_title .. "</comictitle>"
    ----------------------------------------------------------------------------

    ----------------------------------------------------------------------------
    result = result .. "<volumeinfolist>"
    local volume_info_list, errmsg = ComicPageAnalyse_GetVolumeInfoList(comic_page_url, pagestr)
    if not volume_info_list then return nil, "ComicPageAnalyse failed because: " .. errmsg end
    for _, v in pairs(volume_info_list) do
        result = result .. "<volumeinfo>"
        result = result .. "<volumetitle>" .. v.title .. "</volumetitle>"
        result = result .. "<volumeurl>" .. v.url .. "</volumeurl>"
        result = result .. "</volumeinfo>"
    end
    result = result .. "</volumeinfolist>"
    ----------------------------------------------------------------------------
    result = result .. "</result>"

    return result
end

function ComicPageAnalyse_GetComicTitle(pagestr)
    local start_index = JumpStr(pagestr, 1, "<h1>", 1)
    if type(start_index) ~= "number" then return nil, "Getting comic title from pagestr failed" end
    local title = GetStr(pagestr, start_index, "<")
    if not title then return nil, "Getting comic title until \'<\' failed" end
    return TransUtf8ToAnsi(title)
end

function ComicPageAnalyse_GetVolumeInfoList(url, pagestr)
    local start_index = JumpStr(pagestr, 1, "chpater-list-1", 1)
    if not start_index then return nil, "ComicPageAnalyse_GetVolumeInfoList failed because no chpater-list-1" end
    local end_index = JumpStr(pagestr, start_index, "</div>", 1)
    local info_list = {}
    while true do
        local new_info = {}
        start_index = JumpStr(pagestr, start_index, "<a href=\"", 1)
        if not start_index or start_index > end_index then break end
        new_info.url = GetStr(pagestr, start_index, "\"")
        if not new_info.url then return nil, "ComicPageAnalyse_GetVolumeInfoList failed because no \"" end
        new_info.url = GetURLHost(url) .. new_info.url
        
        start_index = JumpStr(pagestr, start_index, "<span>", 1)
        if not start_index then return nil, "ComicPageAnalyse_GetVolumeInfoList failed because no <span>" end
        new_info.title = TransUtf8ToAnsi(GetStr(pagestr, start_index, "<"))
        if not new_info.title then return nil, "ComicPageAnalyse_GetVolumeInfoList failed because no <" end
        
        table.insert(info_list, new_info)
    end
    return info_list
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
	return TransUtf8ToAnsi(GetStr(analyse_result, temp_start_index, "<"))
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
