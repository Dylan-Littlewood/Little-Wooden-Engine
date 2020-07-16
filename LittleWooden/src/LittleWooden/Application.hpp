#pragma once

#include "LittleWooden/Core.hpp"

#include "LittleWooden/Window.hpp"
#include "LittleWooden/LayerStack.hpp"
#include "LittleWooden/Events/Event.hpp"
#include "LittleWooden/Events/ApplicationEvent.hpp"

#include "ImGui/ImGuiLayer.hpp"


#include "LittleWooden/Renderer/Shader.hpp"
#include "LittleWooden/Renderer/Buffer.hpp"

namespace LittleWooden {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT!
	Application* CreateApplication();

}
