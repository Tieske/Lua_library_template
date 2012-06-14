#ifndef lua_template_h	// TODO: rename definition to a unique name
#define lua_template_h


// Macro to export the API
#ifndef EXPORT_API
	#ifdef WIN32
		#define EXPORT_API __declspec(dllexport)
	#else
		#define EXPORT_API extern
	#endif
#endif  

// TODO: add header implementation (optional)



#endif	
