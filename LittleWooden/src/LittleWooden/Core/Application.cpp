#include "lwpch.hpp"
#include "Application.hpp"


#include "GLFW/glfw3.h"
#include "LittleWooden/Core/Input.hpp"

#include "LittleWooden/Core/Timestep.hpp"

#include "LittleWooden/Renderer/Renderer.hpp"


namespace LittleWooden {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		LW_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LW_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e)
	{
		//LW_CORE_INFO("{0}", e.ToString());
		// Makes the Application::OnWindowClose Event run when a WindowCloseEvent occurs
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(LW_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(LW_BIND_EVENT_FN(Application::OnWindowResize));
		dispatcher.Dispatch<UIClickedEvent>(LW_BIND_EVENT_FN(Application::OnUIClicked));

		for (auto layer : m_LayerStack)
		{
			layer->OnEvent(e);
			if (e.Handled)
				break;
		}

	}

	void Application::Run()
	{
		// infinite loop
		while (m_Running)
		{
			float time = (float)glfwGetTime(); // Change to Platform::GetTime() at some point.
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			// Rendering The ImGui For the Application
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetHeight() == 0 || e.GetWidth() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	bool Application::OnUIClicked(UIClickedEvent& e)
	{
		LW_CORE_INFO("{0}", e.ToString());
		return false;
	}
}
