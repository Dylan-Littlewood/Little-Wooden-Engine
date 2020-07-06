#include "lwpch.hpp"
#include "Application.hpp"

#include "LittleWooden/Input.hpp"

#include <glad/glad.h>

namespace LittleWooden {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		LW_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LW_BIND_EVENT_FN(Application::OnEvent));
	}
	
	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(LW_BIND_EVENT_FN(Application::OnWindowClose));

		//LW_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	
	void Application::Run()
	{
		// infinite loop
		while (m_Running)
		{
			glClearColor(0.5f, 0.5f, 0.5f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//auto [x, y] = Input::GetMousePosition();
			//LW_CORE_TRACE("X:{0}, Y:{1}", x, y);

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
