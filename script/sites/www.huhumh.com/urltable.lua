------------------------------------------------------------
---http://www.huhumh.com/
------------------------------------------------------------
-- Get a table contains all URLs of pictures of current volume from the pagestr of this volume page.
function GetPicUrlTableFromVolumePage(pagestr)
    local start_index = JumpStr(pagestr, 1, "PicListUrl", 1);
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping PicListUrl"
    end
    start_index = JumpStr(pagestr, start_index, "\"", 1);
    if type(start_index) ~= "number" then
        return nil, function_name .. "failed when jumping \""
    end
    local pic_url_str = GetStr(pagestr, start_index, "\"")
    if type(pic_url_str) ~= "string" then
        return nil, function_name .. "failed when getting picture url str"
    end
    return unsuan(pic_url_str, "tazsicoewrn") -- the second parameter came from javascript file "/hh/ai.js"
end
