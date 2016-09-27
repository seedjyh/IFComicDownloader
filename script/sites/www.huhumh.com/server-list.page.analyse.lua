function LoadServerList(server_list_url)
    local pagestr, err = DownloadURL(server_list_url, "", "")
    if not pagestr then return "download server_list_url failed, " .. err end

    return ServerListPageAnalyse(server_list_url, pagestr)
end

function ServerListPageAnalyse(url, pagestr)
    local result = {}
    local start_index = JumpStr(pagestr, 1, 'Array(', 1)
    if not start_index then return nil, "Search Array( failed" end
    local server_count_str = GetStr(pagestr, start_index, ")")
    for i = 1,tonumber(server_count_str),1 do
        start_index = JumpStr(pagestr, start_index, "ServerList[", 1)
        if not start_index then break end
        local url_index_str = GetStr(pagestr, start_index, "]")
        if not url_index_str then return nil, "No valid url index" end
        start_index = JumpStr(pagestr, start_index, "]=\"", 1)
        if not start_index then return nil, "No ]=\"" end
        local new_url = GetStr(pagestr, start_index, "\"")
        result[tonumber(url_index_str)] = new_url
    end
    return result
end
