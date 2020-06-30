#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace LWE {

	class LWE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


// Core Log Macros
#define LWE_CORE_TRACE(...)    ::LWE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LWE_CORE_INFO(...)     ::LWE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LWE_CORE_WARN(...)     ::LWE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LWE_CORE_ERROR(...)    ::LWE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LWE_CORE_CRITICAL(...) ::LWE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log Macros
#define LWE_TRACE(...)         ::LWE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LWE_INFO(...)          ::LWE::Log::GetClientLogger()->info(__VA_ARGS__)
#define LWE_WARN(...)          ::LWE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LWE_ERROR(...)         ::LWE::Log::GetClientLogger()->error(__VA_ARGS__)
#define LWE_CRITICAL(...)      ::LWE::Log::GetClientLogger()->critical(__VA_ARGS__)

