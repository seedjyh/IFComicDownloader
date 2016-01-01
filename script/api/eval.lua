--计算eval脚本的函数
function eval(evalstr)
    local use_letter_as_module_index = UseLetterAsModuleIndex(evalstr)
    local module_str = GetModuleString(evalstr)
    local data_str   = GetDataString(evalstr)
    local data_spliter = GetSpliterString(evalstr)
    local data_list, data_size = Split(data_str, data_spliter)
    local result = ReplaceValue(module_str, data_list, use_letter_as_module_index)
    return result
end

--判断是否使用带字母的module index
function UseLetterAsModuleIndex(evalstr)
    local start_index = JumpStr(evalstr, 1, "fromCharCode", 1)
    if type(start_index) ~= "number" then
        return 0
    else
        return 1
    end
end

--从eval字符串里取得模式字符串
function GetModuleString(evalstr)
    local start_index = JumpStr(evalstr, 1, "return p;}", 1)
    if type(start_index) ~= "number" then return nil end
    
    start_index = JumpStr(evalstr, start_index, "\'", 1)
    if type(start_index) ~= "number" then return nil end
    
    local result = GetStr(evalstr, start_index, "\'")
    if type(result) ~= "string" then return nil end
    
    return result
end

--从eval字符串里取得数据字符串
function GetDataString(evalstr)
    local start_index = JumpStr(evalstr, 1, "return p;}", 1)
    if type(start_index) ~= "number" then return nil end
    
    start_index = JumpStr(evalstr, start_index, "\'", 3)
    if type(start_index) ~= "number" then return nil end
    
    local result = GetStr(evalstr, start_index, "\'")
    if type(result) ~= "string" then return nil end
    
    return result
end

--从eval字符串里取得分隔符号
function GetSpliterString(evalstr)
    local start_index = JumpStr(evalstr, 1, "split(\'", 1)
    if type(start_index) ~= "number" then return nil end
    
    local result = GetStr(evalstr, start_index, "\'")
    if type(result) ~= "string" then return nil end
    
    return result
end

--将数据串按照分隔符号分隔成数组（带有长度）
function Split(src_string, spliter_string)
    local pattern_string = "[" .. spliter_string .. "]"
    local result_list = {}
    local result_size = 0
    
    local start_index = 1
    while true do
        local next_spliter_index, _ = string.find(src_string, pattern_string, start_index)
        if type(next_spliter_index) ~= "number" then break end
        
        result_list[result_size] = string.sub(src_string, start_index, next_spliter_index - 1)
        result_size = result_size + 1
        start_index = next_spliter_index + 1
    end
    if start_index <= string.len(src_string) then
        result_list[result_size] = string.sub(src_string, start_index, string.len(src_string))
        result_size = result_size + 1
    end
    
    return result_list, result_size
end

--将模式字符串的模式替换为数据
function ReplaceValue(module_str, value_list, use_letter_as_module_index)
    local number_part_list     = {}
    local number_part_size     = 0
    local non_number_part_list = {}
    local non_number_part_size = 0
    
    if 1 == use_letter_as_module_index then
        number_gmatch_str     = "[%d%a]+"
        non_number_gmatch_str = "[^%d^%a]+"
    else
        number_gmatch_str     = "[%d]+"
        non_number_gmatch_str = "[^%d]+"
    end
    
    for element, iter in string.gmatch(module_str, number_gmatch_str) do
        number_part_list[number_part_size] = element
        number_part_size = number_part_size + 1
    end
    
    for element, iter in string.gmatch(module_str, non_number_gmatch_str) do
        non_number_part_list[non_number_part_size] = element
        non_number_part_size = non_number_part_size + 1
    end

    local result = ""
    local first_str, _ = string.find(module_str, "[%d%a]+")
    local i = 0
    local j = 0
    if first_str ~= 1 then
        i = -1
    end
    while true do
        if i >= number_part_size and j >= non_number_part_size then break end
        
        if i < number_part_size and i >= 0 then
            local str_to_append = value_list[TransStringToEvalStyleNumber(number_part_list[i], use_letter_as_module_index)]
            if 0 == string.len(str_to_append) then
                str_to_append = number_part_list[i]
            end
            result = result .. str_to_append
        end

        if j < non_number_part_size then
            result = result .. non_number_part_list[j]
        end
        
        i = i + 1
        j = j + 1
    end
    
    return result
end

function TransStringToEvalStyleNumber(str, use_letter_as_module_index)
    local result = 0
    local mode_str = "0123456789"
    if 1 == use_letter_as_module_index then
        mode_str = mode_str .. "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    end
    
    for i = 1, string.len(str), 1 do
        result = result * string.len(mode_str)
        now_char = string.sub(str, i, i)
        now_number, _ = string.find(mode_str, now_char)
        result = result + now_number - 1
    end
    return result
end
