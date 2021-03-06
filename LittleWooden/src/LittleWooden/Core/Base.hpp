#pragma once

#include <memory>

#ifdef LW_DEBUG
	#define LW_ENABLE_ASSERTS
#endif

#ifdef LW_ENABLE_ASSERTS
	#define LW_ASSERT(x, ...) { if(!(x)) { LW_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LW_CORE_ASSERT(x, ...) { if(!(x)) { LW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LW_ASSERT(x, ...)
	#define LW_CORE_ASSERT(x, ...)
#endif // LW_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define LW_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) \
{ return this->fn(std::forward<decltype(args)>(args)...); }

namespace LittleWooden {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
