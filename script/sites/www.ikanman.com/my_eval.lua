-- 本函数用于处理ikanmabn.com特有的eval混淆函数。
-- 特殊之处在于使用了类似unsuan那种从一个长字符串里用特定子串作为分隔符的方法加密。
-- 下面的代码来自http://www.ikanman.com/comic/8080/301924.html，经过了适当格式化。
-- window["\x65\x76\x61\x6c"](
-- 	function (p, a, c, k, e, d) {
-- 	e = function (c) {
-- 		return (c < a ? "" : e(parseInt(c / a))) + ((c = c % a) > 35 ? String.fromCharCode(c + 29) : c.toString(36))
-- 	};
-- 	if (!''.replace(/^/, String)) {
-- 		while (c--)
-- 			d[e(c)] = k[c] || e(c);
-- 		k = [function (e) {
-- 				return d[e]
-- 			}
-- 		];
-- 		e = function () {
-- 			return '\\w+'
-- 		};
-- 		c = 1;
-- 	};
-- 	while (c--)
-- 		if (k[c])
-- 			p = p.replace(new RegExp('\\b' + e(c) + '\\b', 'g'), k[c]);
-- 	return p;
-- }
-- 	(
-- 	'v u={"x":5,"w":"t","q":"5.3","p":s,"r":"6","E":["D.3.2","G.3.2","F.3.2","C.3.2","z.4.2","y.3.2","B.3.2","A.4.2","e.4.2","c.3.2","d.4.2","a.4.2","9.3.2","7.4.2","8.3.2","l.3.2","k.3.2","m.3.2","o.3.2","n.3.2","g.3.2","f.3.2","h.3.2","j.3.2","i.3.2","H.3.2","14.3.2","13.3.2","16.3.2","15.3.2","10.3.2","Z.3.2","12.3.2","11.3.2","1d.3.2","1c.3.2","1e.3.2","1b.4.2","17.3.2","1a.3.2","19.4.2","18.4.2","Y.3.2","N.3.2","M.3.2","P.3.2","O.3.2"],"J":I,"L":K,"V":"/U/b/X/6/","W":1,"R":"","Q":0,"T":S}||{};',
-- 	62,
-- 	77,
-- 	'D7DuFMCMAdgK2gc2NAdsgHABm8QNN4AsAzIHtqwAjAQPoEBsGAnBQKw0DsBBFRVtBu5AEy825ZiHJYqRDG3HlyVNrQZtgDKuWUZgg4UWaNditkQZNBPUUSy7WdQRerNaWim01Y9FWlQyU1cgwlDFDdKUMGW3INZgIsJgBjAEsAE2AYZMTgRNQAQwBbcGAbGMEuQEfbQCg7QFjwwFLjHIBJVAAzAHtgADc8gCcM/KKMtOBfZhjbVj5aW2Cg82APQS0dagZ/QQoqFyINluSAG3AAZxLeBiIiXWkDS8FfbHPgFrz9o+K91GSjgAtwdII1IdUMACKwMHomJwtoJRCCPKpHnQqAxaMwNqhwAAPAAujXSkH2bUSAGsqIlso5pjCUD1wJ08SgjuQUHlsd9gEdsayAK4nABCyTaPUQABUeslPtiAJ4gniGcElYSyfglRQKFElaiiJYlHg7NyCWbKWww6FYLg2aRYIhqRyaORqMyaOK0EHCNhYZjiAhqlQbeI0DDxErBaYyEq+VyWEqsO5YV02mgA5hAA'['\x73\x70\x6c\x69\x63']('\x7c'),
-- 	0,
-- 	{}
-- 	)
-- 	)
function MyJavascriptEval(eval_str)
	-- print('------enter MyJavascriptEval: eval_str', eval_str) -- eval_str: "function(p,a,c,k,e,d){...}('u t={...}||{};',62,77,'...',0,{})"
	local module_str = getModule(eval_str)
	-- print('------module', module_str)
	
	local key_str = getEncryptionKey(eval_str)
	-- print('------key', key_str)
	
	local key_dict = StringSplit(LZString_decompresFromBase64(key_str), '|')
	-- print('------dict', key_dict)
	
	local final_dict = tranformKeyDict(key_dict)
	-- print('------final_dict', final_dict)
	
	local plain_str = replaceByFinalDict(module_str, final_dict)
	-- print('------plain_str', plain_str)
	return plain_str
end

-- 从eval_str提取出模板串，也就是'v u={...}||{};'的部分，返回一个字符串。
function getModule(eval_str)
	local start_index = JumpStr(eval_str, 1, "return p;}('", 1)
	return GetStr(eval_str, start_index, "'")
end

-- 从eval_str提取出密钥（密文-明文转换表），返回一个dict。
function getEncryptionKey(eval_str)
	local start_index = JumpStr(eval_str, 1, "}||{};',", 1)
	start_index = JumpStr(eval_str, start_index, "'", 1)
	return GetStr(eval_str, start_index, "'")
end

-- 将模式串按照密钥字段替换，返回替换结果
function replaceByFinalDict(module_str, final_dict)
	local result = ''
	while true do
		local u,v = string.find(module_str, '%w+')
		if u == nil then
			result = result .. module_str
			break
		else -- 找到了！字母数字混合串
			local str_before_key = string.sub(module_str, 1, u - 1)
			local key = string.sub(module_str, u, v)
			local value = final_dict[string.sub(module_str, u, v)]
			if value == nil then value = key end
			result = result .. str_before_key .. value
			module_str = string.sub(module_str, v + 1, -1)
		end
	end
	return result
end

-- 从“数字->明文”的key_dict，转换成“62进制字符串->明文”的dict
-- 62进制指的是0~9然后a~z然后A~Z然后进一位。
function tranformKeyDict(key_dict)
	local final_dict = {}
	for i,v in ipairs(key_dict) do
		local final_key = transformBaseFrom10to62(i - 1) -- 之所以要-1是因为Lua里的数组从1开始，所以循环时下标也是从1开始的。但62进制是从0开始的。
		local final_value = final_key
		if string.len(v) > 0 then
			final_value = v
		end
		final_dict[final_key] = final_value
	end
	return final_dict
end

-- 将整数num转化成62进制字符串。返回字符串。
function transformBaseFrom10to62(num)
	local base_str = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	local result = ''
	if num == 0 then return '0' end
	while num > 0 do
		local new_digit = num % string.len(base_str)
		result = string.sub(base_str, new_digit + 1, new_digit + 1) .. result
		num = math.floor(num / string.len(base_str))
	end
	return result
end









