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

// Close method called when Lua shutsdown the library
static int L_closeLib(lua_State *L) {


	// TODO: add shutdown/cleanup code


}

// Setup a userdata to provide a close method
static void L_setupClose(lua_State *L) {
	// create library tracking userdata
	if (lua_newuserdata(L, sizeof(void*)) == NULL) {
		luaL_error(L, "Cannot allocate userdata");
	};
	// Create a new metatable for the tracking userdata
	luaL_newmetatable(L, "lua_template.MT");	// TODO: update name
	// Add GC metamethod
	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, L_closeLib);
	lua_settable(L, -3);
	// Attach metatable to userdata
	lua_setmetatable(L, -2);
	// pop userdata
	lua_pop(L,1);
}

EXPORT_API	int luaopen_lua_template(lua_State *L){	// TODO: rename to 'luaopen_<LIBRARY_FILENAME>'

	// Setup a userdata with metatable to create a close method
	L_setupClose(L);



	// TODO: add initialization code



	// Export Lua API
	luaL_register(L,"lua_template",LuaExportFunctions);	// TODO: set proper name, table name accessible from Lua
	return 1;
};


