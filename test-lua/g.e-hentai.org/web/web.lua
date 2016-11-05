----------------------------------------------------------------------------------------------------
--  IFComicDownload的lua脚本本地测试工具 ver 2.0
--  2016-11-5 12:24:48 by seedjyh@gmail.com
----------------------------------------------------------------------------------------------------
-- 这个脚本文件对外提供的接口只有一个：SiteDownloadURL
-- 具体功能见该函数开头的注释。

----------------------------------------------------------------------------------
-- 所有和这个网站脚本测试需要（仅和该站有关）的资源都存储在这个路径内。
s_site_path = 'M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\g.e-hentai.org\\'
-- 所有缓存在本地的网页文件都在这个路径内。这样可以避免重复下载。
s_page_path = s_site_path .. 'web\\page\\'
-- 下面将URL到网页缓存文件的映射关系存储在这张表中s_map_url_to_page_file。
s_map_url_to_page_file = {}
s_map_url_to_page_file['http://g.e-hentai.org/g/224263/e06fcdd082/'] = s_page_path .. 'comic_page.html'
s_map_url_to_page_file['http://g.e-hentai.org/g/224263/e06fcdd082/'] = s_page_path .. 'volume_page_home.html'
s_map_url_to_page_file['http://g.e-hentai.org/g/224263/e06fcdd082/?p=1'] = s_page_path .. 'volume_page_extra_1.html'
s_map_url_to_page_file['http://g.e-hentai.org/g/224263/e06fcdd082/?p=2'] = s_page_path .. 'volume_page_extra_2.html'
----------------------------------------------------------------------------------

-- 模拟下载一个网页。实际上是从page目录读文件。
-- 参数：url：待下载的网页URL。
-- 返回：如果这个URL没有预设到映射表，或者无法打开并读取该URL映射到的本地路径文件，则返回nil，第二个参数返回一个字符串说明错误原因。
function DownloadURL(url, ref_url, cookies)
    FUNCTION_NAME='SiteDownloadURL(url=\'' .. url .. '\')'
    
    local file_path = s_map_url_to_page_file[url]
    if not file_path then
        return nil, FUNCTION_NAME .. ': No related file path from this URL'
    end

    local file_data, errmsg = ReadFile(file_path)
    if not file_data then
        return nil, FUNCTION_NAME .. ': cannot read file (path=\'' .. file_path .. '\'), because: ' .. errmsg
    end
    
    return file_data
end
