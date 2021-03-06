------------------------------------------------------------
---http://www.dm5.com/
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
    ----------------------------------------------------------
    local result_end_index=JumpStr(pagestr, 1, "mhinfo", 1)
    if type(result_end_index) ~= "number" then
        return nil, "JumpStr mhinfo failed"
    end

    result_end_index = JumpStr(pagestr, 1, "<h1 class=\"inbt_title_h2\">", 1)
    if type(result_end_index) ~= "number" then
        result_end_index = JumpStr(pagestr, 1, "<h1 class=\"new_h2\">", 1)
        if type(result_end_index) ~= "number" then
            return nil, "JumpStr before comic title failed"
        end
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
    local page_start_index = JumpStr(pagestr, 1, "<ul class=\"nr6 lan2\"", 1)
    if type(page_start_index) ~= "number" then
        return nil, "No <div class=\"bt2\">, the beginning of Volume url list"
    end

    local page_end_index = JumpStr(pagestr, page_start_index, "AddShowHide", 1)
    if type(page_end_index) ~= "number" then
        return nil, "Unknown format: no \"AddShowHide\" for end of volume list"
    end
    
    local index_in_page = page_start_index
    while true do
        -- get relative URL for volume
        index_in_page = JumpStr(pagestr, index_in_page, "<a class=\"tg\"", 1)
        if type(index_in_page) ~= "number" then
            break
        end
        if index_in_page >= page_end_index then
            break
        end
        
        index_in_page = JumpStr(pagestr, index_in_page, "href=\"", 1)
        if type(index_in_page) ~= "number" then
            break
        end
        if index_in_page >= page_end_index then
            break
        end

        local volume_relative_url = GetStr(pagestr, index_in_page, "\"")
        if type(volume_relative_url) ~= "string" then
            return nil, "Unknown format: no \" for <a href=\""
        end
        
        -- get title for volume
        index_in_page = JumpStr(pagestr, index_in_page, ">", 1)
        if type(index_in_page) ~= "number" then
            return nil, "Unknown format: no title \'>\' for this volume"
        end
        
        local volume_title = GetStr(pagestr, index_in_page, "<")
        if type(volume_title) ~= "string" then
            return nil, "Unknown format: no end \" for this volume\'s title"
        end
        
        result = result .. "<volumeinfo>"
        result = result .. "<volumetitle>" .. volume_title .. "</volumetitle>"
        result = result .. "<volumeurl>" .. GetURLHost(comic_page_url) .. volume_relative_url .. "</volumeurl>"
        result = result .. "</volumeinfo>"
    end

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

    return TransUtf8ToAnsi(GetStr(analyse_result, result_end_index, "<"))
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
