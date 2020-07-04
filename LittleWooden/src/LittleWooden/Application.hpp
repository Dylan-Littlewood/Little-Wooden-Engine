#pragma once

#include "Core.hpp"
#include "Window.hpp"
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"

namespace LittleWooden {

	class LW_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT!
	Application* CreateApplication();

}
