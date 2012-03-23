#include <lua.h>
#include <lauxlib.h>
#include "lua_template.h"


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
**   Lua API
** ===============================================================
*/

	// example somefunction
	int L_somefunction(lua_State *L)
	{
		// TODO: add implementation

		return 0;	// number of return values on the Lua stack
	};


/*
** ===============================================================
** Library initialization
** ===============================================================
*/

	// Structure with all functions made available to Lua
	static const struct luaL_Reg LuaSignal[] = {
		{"somefunction",L_somefunction},
		{NULL,NULL}
	};

EXPORT_API	int luaopen_luasignal(lua_State *L){
		luaL_register(L,"lua_template",LuaSignal);	// TODO: set proper name
		return 1;
	};


