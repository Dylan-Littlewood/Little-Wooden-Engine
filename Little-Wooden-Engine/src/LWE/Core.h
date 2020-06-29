#pragma once

#ifdef LWE_PLATFORM_WINDOWS
	#ifdef LWE_BUILD_DLL
		#define LWE_API __declspec(dllexport)
	#else
		#define LWE_API __declspec(dllimport)
	#endif // LWE_API Import/Export
#else
	#error Little Wooden Engine Only Suports Windows!
#endif // LWE_PLATFORM_WINDOWS
