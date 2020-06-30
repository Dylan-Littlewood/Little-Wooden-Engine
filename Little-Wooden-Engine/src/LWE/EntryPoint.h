#pragma once

#ifdef LWE_PLATFORM_WINDOWS
	
	//LWE Application EntryPoint Setup
	extern LWE::Application* LWE::CreateApplication();

	int main(int argc, char** argv)
	{
		LWE::Log::Init();
		LWE_CORE_WARN("Initialized Core Log!");
		LWE_INFO("Initialized Client Log!");
		LWE_TRACE("Welcome!!!");

		auto app = LWE::CreateApplication();
		app->Run();
		delete app;
	}

#endif // LWE_PLATFORM_WINDOWS
