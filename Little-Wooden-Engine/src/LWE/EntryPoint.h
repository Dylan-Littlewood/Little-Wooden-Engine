#pragma once

#ifdef LWE_PLATFORM_WINDOWS
	
	//Application EntryPoint Setup
	extern LWE::Application* LWE::CreateApplication();

	int main(int argc, char** argv)
	{
		auto app = LWE::CreateApplication();
		app->Run();
		delete app;
	}

#endif // LWE_PLATFORM_WINDOWS
