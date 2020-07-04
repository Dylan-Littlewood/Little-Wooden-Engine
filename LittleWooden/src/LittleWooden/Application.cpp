#include "lwpch.hpp"
#include "Application.hpp"

#include "Log.hpp"

#include <GLFW/glfw3.h>

namespace LittleWooden {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	
	Application::~Application()
	{

	}

	void Application::Run()
	{
		// infinite loop
		while (m_Running)
		{
			glClearColor(0,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
