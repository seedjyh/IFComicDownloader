function SiteCheck(x)
	local _, result_end_index=string.find(x, site_mode, 1)
    if type(result_end_index) ~= "number" then
        return 0
    end
    return 1
end

function GetSiteName()
	return site_chinese_name
end

function GetWorkingThreadCount()
	return site_thread_count
end

function GetResourceCoolDownSeconds()
    return site_resource_CD
end

function GetSiteHostURL()
	return site_host
end
