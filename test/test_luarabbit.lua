
-- luarabbit simple tests

local lr = require "luarabbit"

local function stohex(s)  -- return the hex representation of a string
	return s:gsub(".", function(c)
		return string.format("%02x", string.byte(c))
		end)
end

local function hextos(h) -- parse a hex string
	return h:gsub("%s", ""):gsub("..", function(cc)
		return string.char(tonumber(cc, 16))
		end)
end

print("------------------------------------------------------------")
print(_VERSION)

------------------------------------------------------------------------
-- rabbit tests

local stx, xts = stohex, hextos

-- quick test with some eSTREAM test vectors
local key, iv, txt, exp, ec
local key0 = ('\0'):rep(16)
local iv0 = ('\0'):rep(8)
local txt0 = ('\0'):rep(48)
ec = lr.rabbit(txt0, key0, iv0)
exp = xts[[	EDB70567375DCD7CD89554F85E27A7C6
			8D4ADC7032298F7BD4EFF504ACA6295F
			668FBF478ADB2BE51E6CDE292B82DE2A ]]
assert(ec == exp)

iv = xts "2717F4D21A56EBA6"
ec = lr.rabbit(txt0, key0, iv)
exp = xts[[	4D1051A123AFB670BF8D8505C8D85A44
			035BC3ACC667AEAE5B2CF44779F2C896
			CB5115F034F03D31171CA75F89FCCB9F ]]
assert(ec == exp)

--Set 5, vector# 63
iv = xts "0000000000000001"
ec = lr.rabbit(txt0, key0, iv)
exp = xts[[	55FB0B90A9FB953AE96D372BADBEBD30
			F531A454D31B669BCD8BAAD78C6C9994
			FFCCEC7ACB22F914A072DA22A617C0B7 ]]
assert(ec == exp)

--Set6, vector# 0
key = xts "0053A6F94C9FF24598EB3E91E4378ADD"
iv =  xts "0D74DB42A91077DE"
ec = lr.rabbit(txt0, key, iv)
exp = xts[[	75D186D6BC6905C64F1B2DFDD51F7BFC
			D74F926E6976CD0A9B1A3AE9DD8CB43F
			F5CD60F2541FF7F22C5C70CE07613989 ]]
assert(ec == exp)


------------------------------------------------------------------------
print("test_luarabbit", "ok")

return true
