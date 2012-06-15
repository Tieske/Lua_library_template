#include <lua.h>
#include <lauxlib.h>
#include "lua_template.h"	// TODO: rename


/*
** ===============================================================
**   Declarations
** ===============================================================
*/

// TODO: add declarations

/*
** ===============================================================
**   Generic internal code
** ===============================================================
*/

// TODO: add generic code

/*
** ===============================================================
**   Exposed Lua API
** ===============================================================
*/

// TODO: example somefunction, add more here
int L_somefunction(lua_State *L)
{
	// TODO: add implementation
	lua_getglobal(L, "print");
	lua_pushstring(L, "Now running somefunction...");
	lua_call(L, 1, 0);



	return 0;	// number of return values on the Lua stack
};


/*
** ===============================================================
** Library initialization and shutdown
** ===============================================================
*/

// Structure with all functions made available to Lua
static const struct luaL_Reg LuaExportFunctions[] = {
	{"somefunction",L_somefunction},		

	// TODO: add functions from 'exposed Lua API' section above

	{NULL,NULL}
};

// Open method called when Lua opens the library
// On success; push module table on stack and return 1
// On error; push errorstring on stack and return 0
static int L_openLib(lua_State *L) {



	// TODO: add startup/initialization code
	lua_getglobal(L, "print");
	lua_pushstring(L, "Now initializing the Lua template library");
	lua_call(L, 1, 0);





	return 1;	// report success
}


// Close method called when Lua shutsdown the library
// Note: check Lua os.exit() function for exceptions,
// it will not always be called!
static int L_closeLib(lua_State *L) {


	// TODO: add shutdown/cleanup code
	lua_getglobal(L, "print");
	lua_pushstring(L, "Now closing the Lua template library");
	lua_call(L, 1, 0);




	return 0;
}

// Setup a userdata to provide a close method
static void L_setupClose(lua_State *L) {
	// create library tracking userdata
	if (lua_newuserdata(L, sizeof(void*)) == NULL) {
		luaL_error(L, "Cannot allocate userdata, out of memory?");
	};
	// Create a new metatable for the tracking userdata
	luaL_newmetatable(L, LTLIB_UDATAMT);
	// Add GC metamethod
	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, L_closeLib);
	lua_settable(L, -3);
	// Attach metatable to userdata
	lua_setmetatable(L, -2);
	// store userdata in registry
	lua_setfield(L, LUA_REGISTRYINDEX, LTLIB_UDATANAME);
}

// When initialization fails, removes the userdata and metatable
// again, throws the error stored by L_openLib(), will not return
// Top of stack must hold error string
static void L_openFailed(lua_State *L) {
	// get userdata and remove its metatable
	lua_getfield(L, LUA_REGISTRYINDEX, LTLIB_UDATANAME);
	lua_pushnil(L);
	lua_setmetatable(L, -2);
	// remove userdata
	lua_pushnil(L);
	lua_setfield(L, LUA_REGISTRYINDEX, LTLIB_UDATANAME);
	// throw the error (won't return)
	luaL_error(L, lua_tostring(L, -1));
}

LTLIB_EXPORTAPI	int LTLIB_OPENFUNC (lua_State *L){	

	int result = 0;

	// Setup a userdata with metatable to create a close method
	L_setupClose(L);

	// call initialization code
	result = L_openLib(L);
	if (result == 0) 
	{
		// Init failed, so cleanup
		L_openFailed(L);		// will not return
	}

	// Export Lua API
	luaL_register(L, LTLIB_GLOBALNAME, LuaExportFunctions);	

	return result;
};


