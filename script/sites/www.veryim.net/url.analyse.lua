------------------------------------------------------------
---manhua.dmzj.com
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
site_mode = ".veryim.net" -- .XXX.com
site_chinese_name = "VERYIMÂþ»­Íø" --XXXXX
site_thread_count = 100 -- 1~100
site_resource_CD  = 0 -- second
site_host = "http://www.veryim.net/" --http://www.XXX.com/
------------------------------------------------------------
function GetPageType(url)
    -- comic   page URL sample: http://www.veryim.net/manhua/weichengniante
    -- volume  page URL sample: http://www.veryim.net/chapter.php?id=5611
    -- picture page URL sample: http://www.veryim.net/chapter.php?id=5611&p=1
    local last_slash_index = JumpStr(url, 1, '/', 4)
    if type(last_slash_index) == "number" then
        return "comic"
    else
        if JumpStr(url, 1, '&', 1) == "number" then
            return "picture"
        else
            return "volume"
        end
    end
end
