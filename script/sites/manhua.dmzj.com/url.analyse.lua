------------------------------------------------------------
---manhua.dmzj.com
------------------------------------------------------------
function Analyse(url)
    local pagestr = DownloadURL(url, "", "")

    local page_type = GetPageType(url)
    if type(page_type) ~= "string" then
        return nil, "GetPageType failed for url:" .. url
    end
    -- guess the type of page
    if "comic" == page_type then
        return ComicPageAnalyse(url, pagestr, "")
    end
    if "volume" == page_type then
        return VolumePageAnalyse(url, pagestr, "")
    end
    if "picture" == page_type then
        return PicturePageAnalyse(url, pagestr, "")
    end
    return nil, "Unknown page type:" .. page_type .. " for url:" .. url
end
------------------------------------------------------------
site_mode = ".dmzj.com" -- .XXX.com
site_chinese_name = "����֮��������" --XXXXX
site_thread_count = 100 -- 1~100
site_resource_CD  = 0 -- second
site_host = "http://manhua.dmzj.com/" --http://www.XXX.com
------------------------------------------------------------
function GetPageType(url)
    -- comic   page URL sample: http://manhua.dmzj.com/akb49/
    -- volume  page URL sample: http://manhua.dmzj.com/akb49/20657.shtml
    -- picture page URL sample: http://manhua.dmzj.com/akb49/20657-1.shtml
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
