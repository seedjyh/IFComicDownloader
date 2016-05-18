--计算eval脚本的函数
function eval(evalstr)
    local use_letter_as_module_index = UseLetterAsModuleIndex(evalstr)
    
    local module_str, err = GetModuleString(evalstr)
    if type(module_str) ~= "string" then
        return nil, "GetModuleString failed, because:\n" .. err
    end

    local data_str, err   = GetDataString(evalstr)
    if type(data_str) ~= "string" then
        return nil, "GetDataString failed, because:\n" .. err
    end

    local data_spliter, err = GetSpliterString(evalstr)
    if type(data_spliter) ~= "string" then
        return nil, "GetSpliterString failed, because:\n" .. err
    end

    local data_list, data_size, err = Split(data_str, data_spliter)
    if type(data_list) ~= "table" then
        return "Split failed, because:\n" .. err
    end

    local result, err = ReplaceValue(module_str, data_list, use_letter_as_module_index)
    if type(result) ~= "string" then
        return nil, "ReplaceValue failed, because:\n" .. err
    end
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
    if type(evalstr) ~= "string" then
        return nil, "evalstr is not a string, its type is " .. type(evalstr)
    end
    local start_index = JumpStr(evalstr, 1, "return p;}", 1)
    if type(start_index) ~= "number" then
        return nil, "JumpStr failed when jumping return p;}. the cyphertext is: " .. evalstr .. ", length is " .. string.len(evalstr)
    end

    -- 要获取一对单引号引起的字符串。此时要排除转义单引号的影响。
    start_index = JumpStr(evalstr, start_index, "\'", 1)
    if type(start_index) ~= "number" then
        return nil, "JumpStr failed when jumping \'"
    end
    
    end_index = JumpStr(evalstr, start_index, "\'", 1, "\\'")
    if type(end_index) ~= "number" then
        return nil, "JumpStr failed when jumping \' and ignore \\'"
    end

    return string.sub(evalstr, start_index, end_index)
end

--从eval字符串里取得数据字符串
function GetDataString(evalstr)
    local start_index = JumpStr(evalstr, 1, "return p;}", 1)
    if type(start_index) ~= "number" then return nil end
    
    start_index = JumpStr(evalstr, start_index, "\'", 3, "\\'")
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
    if type(src_string) ~= "string" then
        return nil, nil, "src_string is not string but " .. type(src_string)
    end
    if type(spliter_string) ~= "string" then
        return nil, nil, "spliter_string is not string but " .. type(spliter_string)
    end

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
    if type(module_str) ~= "string" then
        return nil, "ReplaceValue failed because module_str is not a string. Its type is " .. type(module_str)
    end
    if type(value_list) ~= "table" then
        return nil, "ReplaceValue failed because value_list is not a table. Its type is " .. type(value_list)
    end
    if type(use_letter_as_module_index) ~= "number" then
        return nil, "ReplaceValue failed because use_letter_as_module_index is not a number. Its type is " .. type(use_letter_as_module_index)
    end

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
            local value_index, err = TransStringToEvalStyleNumber(number_part_list[i], use_letter_as_module_index)
            if type(value_index) ~= "number" then
                return nil, "TransStringToEvalStyleNumber failed, because:\n" .. err
            end

            local str_to_append = value_list[value_index]
            if type(str_to_append) ~= "string" then
                return nil, "value_list[value_index] is not a string. Its type is " .. type(str_to_append) .. ", value_index = " .. value_index
            end
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
    if type(str) ~= "string" then
        return nil, "type of str is not string. its type is " .. type(str)
    end

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
