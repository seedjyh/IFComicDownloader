------------------------------------------------------------
---http://mh.fumanhua.net
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
site_mode = ".fumanhua.net" -- .XXX.com
site_chinese_name = "¸¯Âþ»­" --XXXXX
site_thread_count = 100 -- 1~100
site_resource_CD  = 0 -- second
site_host = "http://mh.fumanhua.net/" --http://www.XXX.com/
------------------------------------------------------------
function GetPageType(url)
    -- comic   page URL sample: http://mh.fumanhua.net/manhua/2947/
    -- volume  page URL sample: http://mh.fumanhua.net/manhua/2947/237854.html
    -- picture page URL sample: http://mh.fumanhua.net/manhua/2947/237854.html?p=3
    if string.find(url, '?') then return "picture" end
    if string.find(url, '.html') then return "volume" end
    return "comic"
end
