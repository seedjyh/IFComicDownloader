function JumpStr(pagestr, start_index, str_to_jump, jump_count)
    local search_start_index = start_index

    for i=1, jump_count do
        local _, result_end_index = string.find(pagestr, str_to_jump, search_start_index, true)
        if type(result_end_index) ~= "number" then
            return nil
        end
        search_start_index = result_end_index + 1
    end

    return search_start_index
end


function GetStr(pagestr, start_index, char_to_end)
    if pagestr == nil then return nil end
    if start_index == nil then return nil end
    
    local _, end_index = string.find(pagestr, "[" .. char_to_end .. "]", start_index)
    if type(end_index) ~= "number" then
        end_index = string.len(pagestr)
    else
        end_index = end_index - 1
    end
    return string.sub(pagestr, start_index, end_index)
end

function GetURLHost(url)
    prefix_length = string.len("http://")
    if string.len(url) > prefix_length then
        slash_index, _ = string.find(url, "/", prefix_length + 1, true)
        if type(slash_index) ~= "number" then
            return url
        end
        return string.sub(url, 1, slash_index - 1)
    end
end

--��ASCII�������ת���ַ�
function AscIICodeToChar(ascii_code)
    assert("number" == type(ascii_code) )
    return string.format("%c", ascii_code)
end

--���ַ�ת��ASCII�������
function CharToAscIICode(char)
    assert("string" == type(char) )
    return tonumber(string.byte(char, 1, 1))
end

--��ʮ�����Ƶ�ASCIIת���ַ�����"67"ת��"g"(0x67)
function HexAscIICodeToChar(hex_ascii)
    local hex_str    = "0x" .. hex_ascii
    local ascii_code = tonumber(hex_str)
    return AscIICodeToChar(ascii_code)
end

--�ҵ�������ĳ�Ӵ���λ��
function GetLastPos(str, substr)
    local result_begin = nil
    local result_end   = nil
    
    local start_index = 1
    while true do
        local temp_begin = nil
        local temp_end   = nil
        temp_begin, temp_end = string.find(str, substr, start_index, true)
        if "number" == type(temp_begin) and "number" == type(temp_end) then
            result_begin = temp_begin
            result_end   = temp_end
            start_index = result_end + 1
        else
            break
        end
    end
    return result_begin, result_end
end

--��str�г���������ender֮����ַ�ȥ��
function CutTailAfterLastKey(str, ender)
    local last_begin = nil
    local last_end   = nil
    local result     = str
    
    last_begin, last_end = GetLastPos(str, ender)
    if "number" == type(last_begin) and "number" == type(last_end) then
        result = string.sub(result, 1, last_end)
    end
    
    return result
end

--��װһ������URL��һ�����URL
function BindURL(absoluted_url, related_url)
    local prefix = absoluted_url
    local suffix = related_url
    local keep_loop = true
    while keep_loop do
        local start_index  = nil
        local finish_index = nil
        
        keep_loop = false
        
        -- XXX + "./XXX"
        start_index, finish_index = string.find(suffix, "./", 1, true)
        if 1 == start_index then
            prefix = CutTailAfterLastKey(prefix, "/")
            suffix = string.sub(suffix, finish_index + 1, string.len(suffix) )
            keep_loop = true
        end
        
        -- XXX + "../XXX"
        start_index, finish_index = string.find(suffix, "../", 1, true)
        if 1 == start_index then
            prefix = CutTailAfterLastKey(prefix, "/")
            prefix = string.sub(prefix, 1, string.len(prefix) - string.len("/") )
            prefix = CutTailAfterLastKey(prefix, "/")
            suffix = string.sub(suffix, finish_index + 1, string.len(suffix) )
            keep_loop = true
        end    
    end
    
    return prefix .. suffix
end

--ȡ��һ���ַ����ӿ�ͷ�����һ��Ŀ�괮���Ӵ�
function GetLongestHost(url)
    local _, end_index = GetLastPos(url, "/")
    return string.sub(url, 1, end_index)
end
