#ifndef lua_template_h	// TODO: rename definition to a unique name
#define lua_template_h	// TODO: rename definition to the same unique name

// TODO: Update module name here
#define LTLIB_LIBRARYNAME    lua_template



// Generate required identifiers from the module name above
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
// name of the global table for the module;		lua_template
#define LTLIB_GLOBALNAME LTLIB_STR(LTLIB_LIBRARYNAME)

// Macro to export the API
#ifndef LTLIB_EXPORTAPI
	#ifdef WIN32
		#define LTLIB_EXPORTAPI __declspec(dllexport)
	#else
		#define LTLIB_EXPORTAPI extern
	#endif
#endif  


#endif	
