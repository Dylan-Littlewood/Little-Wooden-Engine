#include "lwpch.hpp"
#include "Application.hpp"


#include "GLFW/glfw3.h"
#include "LittleWooden/Input.hpp"

#include "LittleWooden/Core/Timestep.hpp"

#include "Renderer/Renderer.hpp"


namespace LittleWooden {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		LW_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LW_BIND_EVENT_FN(Application::OnEvent));

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
		// Makes the Application::OnWindowClose Event run when a WindowCloseEvent occurs
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(LW_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto iterator = m_LayerStack.end(); iterator != m_LayerStack.begin();)
		{
			(*--iterator)->OnEvent(e);
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

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

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
		Exit();
		return true;
	}

	
	// TEMPORARY -- For exit with esc key -- TEMPORARY
	void Application::Exit()
	{
		m_Running = false;
	}
	// TEMPORARY -- For exit with esc key -- TEMPORARY

}
