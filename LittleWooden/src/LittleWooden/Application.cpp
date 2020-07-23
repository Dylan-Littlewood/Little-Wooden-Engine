#include "lwpch.hpp"
#include "Application.hpp"

#include "LittleWooden/Input.hpp"

#include "Renderer/Renderer.hpp"


namespace LittleWooden {

	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		LW_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LW_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Draw a triangle to the screen
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			// triangle points		// Colors of points
			-0.2f, -0.2f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			 0.2f, -0.2f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.2f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_HexVertexArray.reset(VertexArray::Create());

		float hexVertices[3 * 6] = {
			// Hex points
			 0.4f,  0.0f, 0.0f,
			 0.2f,  0.35f, 0.0f,
			-0.2f,  0.35f, 0.0f,
			-0.4f,  0.0f, 0.0f,
			-0.2f, -0.35f, 0.0f,
			 0.2f, -0.35f, 0.0f
		};
		std::shared_ptr<VertexBuffer> hexVB;
		hexVB.reset(VertexBuffer::Create(hexVertices, sizeof(hexVertices)));

		hexVB->SetLayout({ { ShaderDataType::Float3, "a_Position" } });
		m_HexVertexArray->AddVertexBuffer(hexVB);

		unsigned int hexIndices[12] = { 0, 1, 5, 1, 2, 4, 2, 3, 4, 4, 5, 1 };
		std::shared_ptr<IndexBuffer> hexIB;
		hexIB.reset(IndexBuffer::Create(hexIndices, sizeof(hexIndices) / sizeof(uint32_t)));
		m_HexVertexArray->SetIndexBuffer(hexIB);
		
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";


		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		std::string tealShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";


		std::string tealShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.5, 0.5, 1.0);
			}
		)";


		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		m_BlueShader.reset(new Shader(tealShaderVertexSrc, tealShaderFragmentSrc));

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
		// rotating camera
		float t_Rot = 0.0f;

		// infinite loop
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
			RenderCommand::Clear();

			// rotating camera
			m_Camera.SetRotation(t_Rot);

			Renderer::BeginScene(m_Camera);

			Renderer::Submit(m_BlueShader, m_HexVertexArray);
			Renderer::Submit(m_Shader, m_VertexArray);
			
			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// Rendering The ImGui For the Application
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();

			// rotating camera
			t_Rot += 0.1;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
