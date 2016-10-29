-- 测试用例参数列表

assert(ComicPageAnalyse)
assert(VolumePageAnalyse)
assert(PicturePageAnalyse)
assert(GetPageIndexFromURL)

test_case_list = {
    ["comic"] = {
        ["url"] = "http://www.huhumh.com/huhu30134.html",
        ["page"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.huhumh.com\\page\\comic_page.html",
        ["expected_analyse_result"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.huhumh.com\\expected_result\\comic_page.xml",
        ["function_to_test"] = ComicPageAnalyse
    },
    ["volume"] = {
        ["url"] = "http://www.huhumh.com/hu243964/1.html?s=11",
        ["page"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.huhumh.com\\page\\volume_page.html",
        ["expected_analyse_result"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.huhumh.com\\expected_result\\volume_page.xml",
        ["function_to_test"] = VolumePageAnalyse
    },
    ["picture"] = {
        ["url"] = "http://www.huhumh.com/hu243964/1.html?s=11&d=0",
        ["page"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.huhumh.com\\page\\picture_page.html",
        ["expected_analyse_result"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.huhumh.com\\expected_result\\picture_page.xml",
        ["function_to_test"] = PicturePageAnalyse
    },
    
    --["server-list"] = {
    --    ["url"] = "http://www.huhumh.com/hh/ai.js",
    --    ["page"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.huhumh.com\\page\\server-list.js",
    --    ["expected_analyse_result"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.huhumh.com\\expected_result\\server-list_page.xml",
    --    ["function_to_test"] = ServerListPageAnalyse
    --}
}
