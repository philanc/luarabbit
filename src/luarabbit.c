// Copyright (c) 2016  Phil Leblanc  -- see LICENSE file
// ---------------------------------------------------------------------

/*

LuaRabbit

This is a Lua wrapper for the rabbit stream cipher. 

(details about rabbit in the README file and at the top of
the rabbit.c file)

luarabbit API:

rabbit(str, key, iv)
	encrypt (or decrypt, as rabbit is symmetric) string str with 
	key string key and initial value string iv.
	key must be 16 bytes. iv must be 8 bytes
	return the encrypted string (same length as str)
	or nil, error msg if the key or iv lengths are not correct
	-- for more information and references on rabbit, see the comment 
	at the top of src/rabbit.c

encode(str, key, iv)
decode(str, key, iv)
	encode and decode are defined as aliases of the rabbit() 
	symmetrical function.

*/

#define LUARABBIT_VERSION "luarabbit-0.9"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"
#include "rabbit-sync.h"

//=========================================================
// compatibility with Lua 5.2  --and lua 5.3, added 150621
// (from roberto's lpeg 0.10.1 dated 101203)
//
#if (LUA_VERSION_NUM >= 502)

#undef lua_equal
#define lua_equal(L,idx1,idx2)  lua_compare(L,(idx1),(idx2),LUA_OPEQ)

#undef lua_getfenv
#define lua_getfenv	lua_getuservalue
#undef lua_setfenv
#define lua_setfenv	lua_setuservalue

#undef lua_objlen
#define lua_objlen	lua_rawlen

#undef luaL_register
#define luaL_register(L,n,f) \
	{ if ((n) == NULL) luaL_setfuncs(L,f,0); else luaL_newlib(L,f); }

#endif
//=========================================================


//----------------------------------------------------------------------
// rabbit stream cipher
// 
static int lua_rabbit(lua_State *L) {
	// Lua:  
	//	rabbit(plaintext, key, iv) returns encrypted text
	//	rabbit(encrypted, key, iv) returns decrypted text
	//	key: the encryption key - must be a 16-byte string
	//	iv: the initial value -  must be a 8-byte string
	//
    size_t pln, kln, ivln; 
    const char *p = luaL_checklstring (L, 1, &pln);
    const char *k = luaL_checklstring (L, 2, &kln);
    const char *iv = luaL_checklstring (L, 3, &ivln);
	if ((kln != 16) || (ivln != 8)) {
		lua_pushnil (L);
		lua_pushliteral (L, 
			"rabbit key and iv must be 16 and 8 bytes");
		return 2;         
	}
	char * e = malloc(pln); // buffer for encrypted text
	ECRYPT_ctx ctx;
	ECRYPT_keysetup(&ctx, k, 16, 8);
	ECRYPT_ivsetup(&ctx, iv);
	ECRYPT_process_bytes(0, &ctx, p, e, pln); // 1st param is ignored
    lua_pushlstring (L, e, pln); 
    free(e);
    return 1;
}


//------------------------------------------------------------
// lua library declaration
//
static const struct luaL_Reg luarabbitlib[] = {
	{"rabbit", lua_rabbit},
	{"encode", lua_rabbit},   // encode and decode are alias for the 
	{"decode", lua_rabbit},   // symmetrical rabbit() function
	
	{NULL, NULL},
};

int luaopen_luarabbit (lua_State *L) {
	luaL_register (L, "luarabbit", luarabbitlib);
    // 
    lua_pushliteral (L, "VERSION");
	lua_pushliteral (L, LUARABBIT_VERSION); 
	lua_settable (L, -3);
	return 1;
}

