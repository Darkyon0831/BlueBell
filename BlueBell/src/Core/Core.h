#ifndef FMT_DEPRECATED
	#define FMT_DEPRECATED
#endif 

#define BB_API 

#ifndef BB_API
	#ifdef BB_PLATFORM_WINDOWS
		#ifdef BB_BUILD_DLL
			#define BB_API _declspec(dllexport)
		#else
			#define BB_API _declspec(dllimport)
		#endif
	#else
		#error BlueBell can currently only build on windows!!!
	#endif
#endif 

#ifdef _MSC_VER
	#define BB_DISABLE_WARNING_PUSH __pragma(warning( push ))
	#define BB_DISABLE_WARNING(code) __pragma(warning( disable : code ))
	#define BB_DISABLE_WARNING_POP __pragma(warning( pop ))
#endif // _MSC_VER

#define BB_STATIC_ASSERT(expression, ...) static_assert(expression, __VA_ARGS__);

#define BB_NOT_USE(var) (void)var;

