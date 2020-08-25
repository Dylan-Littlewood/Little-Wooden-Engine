#pragma once

#include "LittleWooden/Base.hpp"

#include "ImGui/ImGuiLayer.hpp"


#include "LittleWooden/Window.hpp"
#include "LittleWooden/LayerStack.hpp"
#include "LittleWooden/Events/Event.hpp"
#include "LittleWooden/Events/ApplicationEvent.hpp"



namespace LittleWooden {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		// TEMPORARY -- For exit with esc key -- TEMPORARY
		void Exit();
		// TEMPORARY -- For exit with esc key -- TEMPORARY

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT!
	Application* CreateApplication();

}
