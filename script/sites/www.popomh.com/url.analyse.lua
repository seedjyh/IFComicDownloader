------------------------------------------------------------
---http://www.popomh.com/
------------------------------------------------------------
function Analyse(url)
    local page_type = GetPageType(url)
    if type(page_type) ~= "string" then
        return nil, "GetPageType failed for url:" .. url
    end
    -- guess the type of page
    if "comic" == page_type then
        return ComicUrlAnalyse(url, pagestr, "")
    end
    if "volume" == page_type then
        return VolumeUrlAnalyse(url, pagestr, "")
    end
    if "picture" == page_type then
        return PictureUrlAnalyse(url, pagestr, "")
    end
    return nil, "Unknown page type:" .. page_type .. " for url:" .. url
end
------------------------------------------------------------
site_mode = ".popomh.com" -- .XXX.com
site_chinese_name = "»¢»¢Âþ»­" --XXXXX
site_thread_count = 100 -- 1~100
site_resource_CD  = 0 -- second
site_host = "http://www.popomh.com/" --http://www.XXX.com/
------------------------------------------------------------
function GetPageType(url)
    -- comic   page URL sample: http://www.popomh.com/manhua/21523.html
    -- volume  page URL sample: http://www.popomh.com/popo150259/1.html?s=5
    -- picture page URL sample: http://www.popomh.com/popo150259/1.html?s=5
    local last_slash_index = JumpStr(url, 1, '/', 4)
    if type(last_slash_index) ~= "number" then
        return nil
    end

    if last_slash_index == string.len(url) + 1 then
        return "comic"
    end
    
    local bar_index = JumpStr(url, last_slash_index, "-", 1)
    -- no bar('-') means volume page
    if type(bar_index) ~= "number" then
        return "volume"
    end

    return "picture"
end
