#pragma once

#ifdef LW_PLATFORM_WINDOWS
	#ifdef LW_BUILD_DLL
		#define LW_API __declspec(dllexport)
	#else
		#define LW_API __declspec(dllimport)
	#endif // LW_API Import/Export
#else
	#error Little Wooden Engine Only Suports Windows!
#endif // LW_PLATFORM_WINDOWS
