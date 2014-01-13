#ifndef udtype_h	// TODO: rename definition to a unique name
#define udtype_h	// TODO: rename definition to the same unique name

// TODO: Update module name here
#define LTLIB_LIBRARYNAME    udtype
#if LUA_VERSION_NUM < 502
	// TODO: uncomment line below to export the the module table as a 
	// Lua global, only for 5.1, setting global tables deprecated in 5.2
	//#define LTLIB_CREATEGLOBALTABLE
#endif

/*
** ===============================================================
** Description
** ===============================================================
** 
** Library to extend the type() function, has 1 exported function;
** 
**      udtype.type()
** 
** The function is identical to type() except that it will return a
** second result if the type is a 'userdata', the result will be the
** metatable name of the userdata.
** 
*/

// TODO: add description



/*
** ===============================================================
** Generate required identifiers from the module name above
** ===============================================================
*/

#define LTLIB_STR_EXPAND(a) #a
#define LTLIB_STR(a) LTLIB_STR_EXPAND(a)
#define LTLIB_CONCAT_EXPAND(a,b)  a##b
#define LTLIB_CONCAT(a,b) LTLIB_CONCAT_EXPAND(a,b)
// Name for storing userdata in registry;		"lua_template.lib_udata"
#define LTLIB_UDATANAME  LTLIB_STR( LTLIB_LIBRARYNAME##.lib_udata)
// Name of metatable for userdata;				"lua_template.lib_udata_mt"
#define LTLIB_UDATAMT    LTLIB_STR( LTLIB_LIBRARYNAME##.lib_udata_mt)
// name of luaopen function;					luaopen_lua_template
#define LTLIB_OPENFUNC   LTLIB_CONCAT(luaopen_,LTLIB_LIBRARYNAME)
// name of the global table for the module;		"lua_template" || NULL
#ifdef LTLIB_CREATEGLOBALTABLE
	#define LTLIB_GLOBALNAME LTLIB_STR(LTLIB_LIBRARYNAME)
#else
	#define LTLIB_GLOBALNAME NULL
#endif

// Macro to export the API
#ifndef LTLIB_EXPORTAPI
	#ifdef _WIN32
		#define LTLIB_EXPORTAPI __declspec(dllexport)
	#else
		#define LTLIB_EXPORTAPI extern
	#endif
#endif  


/*
** ===============================================================
**  Other definitions
** ===============================================================
*/

// TODO: Add definitions (optional)

// Reference table with MT; weak table used to store metatables
// already lookedup in the registry, key will be the metatable
// and value the metatable name
#define UDTYPE_TABLE    "udtype.reftable"
#define UDTYPE_TABLEMT  "udtype.reftable_mt"


#endif	
