#pragma once

#include "LittleWooden/Core/Base.hpp"
#include "LittleWooden/Core/Window.hpp"
#include "LittleWooden/Core/LayerStack.hpp"

#include "LittleWooden/Events/Event.hpp"
#include "LittleWooden/Events/ApplicationEvent.hpp"
#include "LittleWooden/Events/UIEvent.hpp"

#include "LittleWooden/ImGui/ImGuiLayer.hpp"


namespace LittleWooden {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		static void CallEvent(Event& e) { Get().GetWindow().CallEvent(e); }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnUIClicked(UIClickedEvent& e);

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
