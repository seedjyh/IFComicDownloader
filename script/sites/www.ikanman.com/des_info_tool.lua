-- Get cipher text from volume page str
function VolumePageAnalyse_GetDesCipherText(pagestr)
    local function_name = "VolumePageAnalyse_GetDesCipherText"
    local start_index = JumpStr(pagestr, 1, "decryptDES('", 1);
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping decryptDES('"
    end
    local des_info_ciphertext = GetStr(pagestr, start_index, "'")
    if type(des_info_ciphertext) ~= "string" then
        return nil, function_name .. "failed when getting des ciphertext"
    end
    return des_info_ciphertext
end

-- Decrypt ciphertext in volume page str
function VolumePageAnalyse_decryptDES(ciphertext)
    local key = string.sub(ciphertext, 1, 8)
    local ciphertext_base64 = string.sub(ciphertext, 9, -1)
    local ciphertext = Base64Decode(ciphertext_base64)
    return DES_Decrypt_ECB_PKCS5(string.len(ciphertext), ciphertext, string.len(key), key)
end

function VolumePageAnalyse_GetPictureCountFromInfo(info)
    local start_index = JumpStr(info, 1, "\"len\":", 1)
    if type(start_index) ~= "number" then return nil end
    
    local count_str = GetStr(info, start_index, ',')

    if type(count_str) ~= "string" then return nil end
    return tonumber(count_str)
end

-- pic_index start from 1
function VolumePageAnalyse_GetFileURL(info, pic_index)
    local start_index = JumpStr(info, 1, "\"files\":[", 1)
    if type(start_index) ~= 'number' then return nil end
    local end_index = JumpStr(info, start_index, ']', 1)
    
    if pic_index > 0 then
        start_index = JumpStr(info, start_index, ',', pic_index - 1)
    end
    
    start_index = JumpStr(info, start_index, '\"', 1)
    local file_relative_url = GetStr(info, start_index, '\"')
    return file_relative_url
end

function VolumePageAnalyse_GetFilePath(info)
    local start_index = JumpStr(info, 1, "\"path\":\"", 1)
    local path = GetStr(info, start_index, '\"')
    return path
end
