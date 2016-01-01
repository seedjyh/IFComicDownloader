function PicturePageAnalyse(picture_page_url, pagestr, extra_info)
    local result = "<result>"

    local start_index = JumpStr(pagestr, 1, "var g_current_page = ", 1)
    if type(start_index) ~= "number" then
        return nil, "error when call JumpStr var g_current_page = "
    end
    
    local picture_index_str = GetStr(pagestr, start_index, ";")
    if type(picture_index_str) ~= "string" then
        return nil, "error when trying to get current index"
    end
    local picture_index_num = tonumber(picture_index_str)
    if type(picture_index_num) ~= "number" then
        return nil, "error when transforming picture index from string to number, string form is: " .. picture_index_str
    end

    start_index = JumpStr(pagestr, 1, "eval(", 1)
    if type(start_index) ~= "number" then
        return nil, "error when looking for eval("
    end
    local eval_str = GetStr(pagestr, start_index, "\n")
    if type(eval_str) ~= "string" then
        return nil, "error when trying to get eval string"
    end

    local eval_str_content, err = JavascriptEval(eval_str)
    if type(eval_str_content) ~= "string" then
        return nil, "error when calculating eval string " .. err
    end
	
	-- KEY CODE HERE!
	local url_start_index = JumpStr(eval_str_content, (picture_index_num - 1) * 2 + 1, "\"", 1)
	local relative_url = GetStr(eval_str_content, url_start_index, "\"")
	local formated_relative_url = string.gsub(relative_url, "\\", "") -- Remove "\\"(0x5c) from URL.
	local file_url = "http://images.dmzj.com" .. "/" .. formated_relative_url
    
    --------------------------------------------------------------------
    result = result .. "<fileurl>"
    result = result .. file_url
    result = result .. "</fileurl>"
    --------------------------------------------------------------------
    result = result .. "<refererurl>"
    result = result .. picture_page_url
    result = result .. "</refererurl>"
    --------------------------------------------------------------------
    result = result .. "</result>"
    
    return result
end

function FindFileUrl(analyse_result)
    local start_index = JumpStr(analyse_result, 1, "<fileurl>", 1)
    if type(start_index) ~= "number" then
        return nil, "error when call JumpStr"
    end

    local file_url = GetStr(analyse_result, start_index, "<")
    if type(file_url) ~= "string" then
        return nil, "error when call GetStr"
    end
    return file_url
end

function FindFileRefererUrl(analyse_result)
    local start_index = JumpStr(analyse_result, 1, "<refererurl>", 1)
    if type(start_index) ~= "number" then
        return nil, "error when call JumpStr"
    end

    local referre_url = GetStr(analyse_result, start_index, "<")
    if type(referre_url) ~= "string" then
        return nil, "error when call GetStr"
    end
    return referre_url
end
