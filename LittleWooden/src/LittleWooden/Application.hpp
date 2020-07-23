#pragma once

#include "LittleWooden/Core.hpp"

#include "ImGui/ImGuiLayer.hpp"

#include "LittleWooden/Window.hpp"
#include "LittleWooden/LayerStack.hpp"

#include "LittleWooden/Events/Event.hpp"
#include "LittleWooden/Events/ApplicationEvent.hpp"

#include "LittleWooden/Renderer/Shader.hpp"
#include "LittleWooden/Renderer/Buffer.hpp"
#include "LittleWooden/Renderer/VertexArray.hpp"
#include "LittleWooden/Renderer/OrthographicCamera.hpp"


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

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<Shader> m_Shader;
		
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexArray> m_HexVertexArray;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT!
	Application* CreateApplication();

}
