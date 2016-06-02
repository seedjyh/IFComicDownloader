------------------------------------------------------------
---slide.sports.sina.com.cn
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
site_mode = ".sina.com.cn" -- .XXX.com
site_chinese_name = "新浪图片" --XXXXX
site_thread_count = 100 -- 1~100
site_resource_CD  = 0 -- second
site_host = "http://*.sina.com.cn/" --http://www.XXX.com/
------------------------------------------------------------
function GetPageType(url)
    -- comic   page URL sample: http://slide.tech.sina.com.cn/notebook/slide_5_37825_69068.html
    -- volume  page URL sample: http://slide.tech.sina.com.cn/notebook/slide_5_37825_69068.html
    -- picture page URL sample: hhttp://slide.tech.sina.com.cn/notebook/slide_5_37825_69068.html#p=1
    local equal_index = JumpStr(url, 1, '=', 1)
    -- 有个等号就是picture。
    if type(equal_index) == "number" then
        return "picture"
    else
        return "comic"
    end
end
