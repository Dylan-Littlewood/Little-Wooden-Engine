#pragma once

#include "LittleWooden/Core/Base.hpp"

#ifdef LW_PLATFORM_WINDOWS
	
	//LW Application EntryPoint Setup
	extern LittleWooden::Application* LittleWooden::CreateApplication();
	

	int main(int argc, char** argv)
	{
		LittleWooden::Log::Init();
		LW_CORE_WARN("Initialized Core Log!");
		LW_INFO("Initialized Client Log!");

		auto app = LittleWooden::CreateApplication();
		app->Run();
		delete app;
	}

#endif // LW_PLATFORM_WINDOWS
