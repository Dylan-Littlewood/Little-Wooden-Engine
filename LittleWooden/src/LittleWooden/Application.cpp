#include "Application.hpp"

#include "LittleWooden/Events/ApplicationEvent.hpp"
#include "Log.hpp"

namespace LittleWooden {

	Application::Application()
	{

	}
	
	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		LW_TRACE(e);
		// infinite loop
		while (true);
	}
}
