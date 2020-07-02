#include "Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace LittleWooden {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// Set the layout of the Log Messages
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// Create and set the level of the Core logger
		s_CoreLogger = spdlog::stdout_color_mt("[Little Wooden Engine]");
		s_CoreLogger->set_level(spdlog::level::trace);

		// Create and set the level of the Client logger
		s_ClientLogger = spdlog::stdout_color_mt("[  Client Application]");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}
