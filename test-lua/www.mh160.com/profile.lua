-- 测试用例参数列表

assert(ComicPageAnalyse)
assert(VolumePageAnalyse)
assert(PicturePageAnalyse)

test_case_list = {
    ["comic"] = {
        ["url"] = "http://www.mh160.com/kanmanhua/25512/",
        ["page"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.mh160.com\\page\\comic_page.html",
        ["expected_analyse_result"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.mh160.com\\expected_result\\comic_page.xml",
        ["function_to_test"] = ComicPageAnalyse
    },
    ["volume"] = {
        ["url"] = "http://www.mh160.com/kanmanhua/25512/433965.html?mode=1",
        ["page"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.mh160.com\\page\\volume_page.html",
        ["expected_analyse_result"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.mh160.com\\expected_result\\volume_page.xml",
        ["function_to_test"] = VolumePageAnalyse
    },
    ["picture"] = {
        ["url"] = "http://www.mh160.com/kanmanhua/25512/433965.html?mode=1&p=1",
        ["page"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.mh160.com\\page\\picture_page.html",
        ["expected_analyse_result"] = "M:\\GitHubRepositories\\IFComicDownloader\\test-lua\\www.mh160.com\\expected_result\\picture_page.xml",
        ["function_to_test"] = PicturePageAnalyse
    }
}
