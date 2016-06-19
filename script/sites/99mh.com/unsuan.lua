---------------------------------------------------------------------------------------------
-- This function is the core decoding function for site 99mh.com.
-- It's defined at javascript file "/script/viewhtm.js" (encrypted).
-- Here is a LUA function to do similar jobs.
---------------------------------------------------------------------------------------------
-- Definition of function "unsuan" in 99mh.com (after decryption)
-- function unsuan(s)
-- {
--     var a="99mh.com|twcomic.com";
--     var c=location.hostname.toLowerCase();
--     b=false;
--     for(i=0;i<a.split("|").length;i++)
--     {
--         if(c.indexOf(a.split("|")[i])>-1)
--         {
--             b=true;
--             break
--         }
--     }
--     
--     if(!b)
--         return"";
-- 
--     var x=s.substring(s.length-1);
--     var d="abcdefghijklmnopqrstuvwxyz".indexOf(x)+1;
--     var e=s.substring(s.length-d-12,s.length-d-1);
--     s=s.substring(0,s.length-d-12);
--     var k=e.substring(0,e.length-1);
--     var f=e.substring(e.length-1);
--     for(i=0; i<k.length; i++){
--         eval("s=s.replace(/"+k.substring(i,i+1)+"/g,'"+i+"')")
--     }
--     
--     var g=s.split(f);
--     s="";
--     for(i=0; i<g.length; i++)
--     {
--         s+=String.fromCharCode(g[i])
--     }
-- 
--     return s
-- }

-------------------------------------------------------------------------------------
-- Return a table of FileURL
-- Let the return value was stored at t, the first URL would be t[1]. Yes it starts from 1.
-------------------------------------------------------------------------------------
function unsuan(sFiles)
    if type(sFiles) ~= "string" then
        return nil, "parameter sFiles is not a string."
    end
    -- variables below has similar meaning as them in javascript unsuan function above.
    local x = string.sub(sFiles, -1, -1)
    local d = string.byte(x) - string.byte('a') + 1 -- start from 1
    local e = string.sub(sFiles, -12-d, -2-d)
    local s = string.sub(sFiles, 0, -12-d-1)
    local k = string.sub(e, 0, -2)
    local f = string.sub(e, -1, -1)

    for i=0,string.len(k)-1 do
        s = string.gsub(s, string.sub(k, i + 1, i + 1), tostring(i))
    end
    unicode_str = ''
    for i,v in ipairs(StringSplit(s, f)) do
        unicode_str = unicode_str .. string.format("%04X", v)
    end
    
    ansi_text = TransBigEndianUnicodeHexToAnsi(string.len(unicode_str), unicode_str)
    return StringSplit(ansi_text, '|')
end

