------------------------------------------------------------
---http://www.ikanman.com/
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
site_mode = ".e-hentai.org" -- .XXX.com
site_chinese_name = "G-Hentai Galleries" --XXXXX
site_thread_count = 100 -- 1~100
site_resource_CD  = 0 -- second
site_host = "http://g.e-hentai.org/" --http://www.XXX.com/
------------------------------------------------------------
function GetPageType(url)
    -- comic   page URL sample: http://g.e-hentai.org/g/523011/263f021d34/
    -- volume  page URL sample: http://g.e-hentai.org/g/523011/263f021d34/
    -- picture page URL sample: http://g.e-hentai.org/s/46ac2039f1/523011-1
    if type(JumpStr(url, 1, '-', 2)) ~= "number" then
        return "volume"
    end

    return "picture"
end
