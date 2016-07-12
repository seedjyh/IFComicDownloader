---------------------------------------------------------------------------------------------
-- This function is the core decoding function for site www.huhumh.com.
-- It's defined at javascript file "/hh/ai.js" (encrypted).
-- Here is a LUA function to do similar jobs.
---------------------------------------------------------------------------------------------
-- Definition of function "unsuan" in www.huhumh.com
-- function unsuan(s,sk) 
-- {
-- 	sw="hhmanhua.net|huhumh.com|hhmanhua.cc";
-- 	su = location.hostname.toLowerCase();
-- 	b=false;
-- 	for(i=0;i<sw.split("|").length;i++) {
-- 	    if(su.indexOf(sw.split("|")[i])>-1) {
-- 	        b=true;
-- 	        break;
--         }
--     }
--     if(!b)return "";
-- 	k=sk.substring(0,sk.length-1);
-- 	f=sk.substring(sk.length-1);
-- 	for(i=0;i<k.length;i++) {
-- 	    eval("s=s.replace(/"+ k.substring(i,i+1) +"/g,'"+ i +"')");
-- 	}
--     ss = s.split(f);
-- 	s="";
-- 	for(i=0;i<ss.length;i++) {
-- 	    s+=String.fromCharCode(ss[i]);
--     }
--     return s;
-- }

-------------------------------------------------------------------------------------
-- Return a table of FileURL
-- Let the return value was stored at t, the first URL would be t[1]. Yes it starts from 1.
-------------------------------------------------------------------------------------
function unsuan(s, sk)
    if type(s) ~= "string" then
        return nil, "parameter s is not a string."
    end
    if type(sk) ~= "string" then
        return nil, "parameter sk is not a string."
    end
    -- variables below has similar meaning as them in javascript unsuan function above.
    local k = string.sub(sk, 0, -2)
    local f = string.sub(sk, -1)
    
    for i=0, string.len(k)-1 do
        s = string.gsub(s, string.sub(k, i+1, i+1), tostring(i))
    end
    
    url_str = ''
    for i, v in ipairs(StringSplit(s, f)) do
        url_str = url_str .. string.format("%c", tonumber(v))
    end
    
    return StringSplit(url_str, '|')
end

