---------------------------------------------------------------------------------------------
-- This function is the core decoding function for site www.popomh.com.
-- It's defined at javascript file "/script/view.js" (encrypted).
-- Here is a LUA function to do similar jobs.
---------------------------------------------------------------------------------------------
-- Definition of function "unsuan" in www.popomh.com
-- function unsuan(s) 
-- {
-- 	sw="hanhan8.cc|popomh.com";
-- 	su = location.hostname.toLowerCase();
-- 	b=false;
-- 	for(i=0;i<sw.split("|").length;i++) {
-- 	    if(su.indexOf(sw.split("|")[i])>-1) {
-- 	        b=true;
-- 	        break;
--         }
--     }
--     if(!b)return "";
--     
--     x = s.substring(s.length-1);
--     w="abcdefghijklmnopqrstuvwxyz";
--     xi=w.indexOf(x)+1;
--     sk = s.substring(s.length-xi-12,s.length-xi-1);
--     s=s.substring(0,s.length-xi-12);    
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
-- Parameter "s" is a ciphertext with file URL.
-- Decrypt the ciphertext and return the file URL hidden in it.
-------------------------------------------------------------------------------------
-- 需要根据新的unsuan函数来开发下面的lua-unsuan函数。
-- 基本上，各变量沿用网站上的unsuan函数。
function unsuan(s)
    local x = string.sub(s, -1)
    local xi = string.byte(x) - string.byte('a') + 1
    local sk = string.sub(s, -xi-12, -xi-2) -- sk长度11
    local s = string.sub(s, 0, -xi-13)
    local k = string.sub(sk, 0, -2)
    local f = string.sub(sk, -1)
    
    for i=0, string.len(k)-1 do
        s = string.gsub(s, string.sub(k, i+1, i+1), tostring(i))
    end
    
    url_str = ''
    for i, v in ipairs(StringSplit(s, f)) do
        url_str = url_str .. string.format("%c", tonumber(v))
    end
    
    return url_str
end

