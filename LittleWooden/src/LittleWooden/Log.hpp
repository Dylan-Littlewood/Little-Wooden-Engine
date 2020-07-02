#pragma once

#include <memory>

#include "Core.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace LittleWooden {

	class LW_API Log
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
#define LW_CORE_TRACE(...)    ::LittleWooden::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LW_CORE_INFO(...)     ::LittleWooden::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LW_CORE_WARN(...)     ::LittleWooden::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LW_CORE_ERROR(...)    ::LittleWooden::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LW_CORE_CRITICAL(...) ::LittleWooden::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log Macros
#define LW_TRACE(...)         ::LittleWooden::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LW_INFO(...)          ::LittleWooden::Log::GetClientLogger()->info(__VA_ARGS__)
#define LW_WARN(...)          ::LittleWooden::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LW_ERROR(...)         ::LittleWooden::Log::GetClientLogger()->error(__VA_ARGS__)
#define LW_CRITICAL(...)      ::LittleWooden::Log::GetClientLogger()->critical(__VA_ARGS__)

