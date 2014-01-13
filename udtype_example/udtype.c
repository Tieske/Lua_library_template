#include <lua.h>
#include <lauxlib.h>
#include "udtype.h"	// TODO: rename

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

#ifdef _DEBUG
//can be found here  http://www.lua.org/pil/24.2.3.html
static void stackDump (lua_State *L, const char *text) {
      int i;
      int top = lua_gettop(L);
	  if (text == NULL)
		printf("--------Start Dump------------\n");
	  else
	    printf("--------Start %s------------\n", text);
      for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
    
          case LUA_TSTRING:  /* strings */
            printf("`%s'", lua_tostring(L, i));
            break;
    
          case LUA_TBOOLEAN:  /* booleans */
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;
    
          case LUA_TNUMBER:  /* numbers */
            printf("%g", lua_tonumber(L, i));
            break;
    
          default:  /* other values */
            printf("%s", lua_typename(L, t));
            break;
    
        }
        printf("  ");  /* put a separator */
      }
      printf("\n");  /* end the listing */
	  printf("--------End Dump------------\n");
    }

static void tableDump(lua_State *L, int idx, const char* text)
{
	lua_pushvalue(L, idx);		// copy target table
	lua_pushnil(L);
	  if (text == NULL)
		printf("--------Table Dump------------\n");
	  else
	    printf("--------Table dump: %s------------\n", text);
	while (lua_next(L,-2) != 0) {
		printf("%s - %s\n",
			lua_typename(L, lua_type(L, -2)),
			lua_typename(L, lua_type(L, -1)));
		lua_pop(L, 1);
	}
	lua_pop(L, 1);	// remove table copy
    printf("--------End Table dump------------\n");
}
#endif

/*
** ===============================================================
**   Exposed Lua API
** ===============================================================
*/

// TODO: example somefunction, add more here
int L_type(lua_State *L)
{

	// perform standard type functionality
	luaL_checkany(L, 1);
	lua_settop(L, 1);															// val
	lua_checkstack(L, 6);
	lua_pushstring(L, luaL_typename(L, 1));										// val, type
	// Now check for userdata and metatable
	if (lua_type(L, 1) == LUA_TUSERDATA) {
		if (lua_getmetatable(L, 1) != 0) {										// val, type, metatable
			// it is a userdata and has a metatable
			lua_getfield(L, LUA_REGISTRYINDEX, UDTYPE_TABLE);					// val, type, metatable, mytable
			lua_insert(L, -2);													// val, type, mytable, metatable
			lua_pushvalue(L, -1);												// val, type, mytable, metatable, metatable
			lua_gettable(L, -3);												// val, type, mytable, metatable, metatablename|nil
			if (! lua_isnil(L,-1)) {
				// metatable was in our list 
				lua_remove(L, -2);												// val, type, mytable, metatablename
				lua_remove(L, -2);												// val, type, metatablename
				return 2;
			} else {
				// metatable isn't in our list already, so go look it up		// val, type, mytable, metatable, nil
				while (lua_next(L, LUA_REGISTRYINDEX) != 0) {					// val, type, mytable, metatable, key, value
#if LUA_VERSION_NUM < 502
					if (lua_equal(L, -3, -1)) {
#else
					if (lua_compare(L, -3, -1, LUA_OPEQ)) {
#endif        
						// found it!											// val, type, mytable, metatable, metatablename, metatable
						lua_remove(L, -3);										// val, type, mytable, metatablename, metatable
						lua_pushvalue(L, -2);									// val, type, mytable, metatablename, metatable, metatablename
						lua_settable(L, 3);										// val, type, mytable, metatablename
						lua_remove(L, -2);										// val, type, metatablename
						return 2;
					}
					lua_pop(L,1);												// val, type, mytable, metatable, key
				}
				// metatable not found, return type only
				lua_settop(L,2);												// val, type
				return 1;
			}
		} else {
			// It is a userdata, without a metatable
			return 1;
		}
	} else {
		return 1;	// just the regular type
	}
};


/*
** ===============================================================
** Library initialization and shutdown
** ===============================================================
*/

// Structure with all functions made available to Lua
static const struct luaL_Reg LuaExportFunctions[] = {

	// TODO: add functions from 'exposed Lua API' section above
	{"type",L_type},		


	{NULL,NULL}
};

// Open method called when Lua opens the library
// On success; return 1
// On error; push errorstring on stack and return 0
static int L_openLib(lua_State *L) {



	// create lookup table for already checked metatables
	lua_newtable(L);
	// set weak keys and values
	luaL_newmetatable(L, UDTYPE_TABLEMT);
	lua_pushstring(L, "k");
	lua_setfield(L, -2, "__mode");
	// store it in registry
	lua_setfield(L, LUA_REGISTRYINDEX, UDTYPE_TABLE);



	return 1;	// report success
}


// Close method called when Lua shutsdown the library
// Note: check Lua os.exit() function for exceptions,
// it will not always be called!
static int L_closeLib(lua_State *L) {


	// TODO: add shutdown/cleanup code




	return 0;
}


/*
** ===============================================================
** Core startup functionality, no need to change anything below
** ===============================================================
*/


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
	lua_newtable(L);
#if LUA_VERSION_NUM < 502
	luaL_register(L, LTLIB_GLOBALNAME, LuaExportFunctions);
#else
	luaL_setfuncs (L, LuaExportFunctions, 0);
#endif        
	return result;
};


