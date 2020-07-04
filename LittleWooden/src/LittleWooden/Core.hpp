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

#ifdef LW_ENABLE_ASSERTS
	#define LW_ASSERT(x, ...) { if(!(x)) { LW_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LW_CORE_ASSERT(x, ...) { if(!(x)) { LW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LW_ASSERT(x, ...)
	#define LW_CORE_ASSERT(x, ...)
#endif // LW_ENABLE_ASSERTS

#define BIT(x) (1 << x)