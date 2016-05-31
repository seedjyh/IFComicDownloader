------------------------------------------------------------
---www.doyo.cn
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
site_mode = ".doyo.cn" -- .XXX.com
site_chinese_name = "逗游图库" --XXXXX
site_thread_count = 100 -- 1~100
site_resource_CD  = 0 -- second
site_host = "http://www.doyo.cn/" --http://www.XXX.com/
------------------------------------------------------------
function GetPageType(url)
    -- comic   page URL sample: http://www.doyo.cn/picture/5177
    -- volume  page URL sample: http://www.doyo.cn/picture/5177/
    -- picture page URL sample: http://www.doyo.cn/picture/5177/1
    local last_slash_index = JumpStr(url, 1, '/', 4)
    -- 有4个斜杠且url最后一个字符不是斜杠，那么就是picture。
    if type(last_slash_index) == "number" and string.sub(string.len(url) - 1) ~= '/' then
        return "picture"
    else
        return "comic"
    end
end
