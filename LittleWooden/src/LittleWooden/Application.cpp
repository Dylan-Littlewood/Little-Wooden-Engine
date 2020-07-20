#include "lwpch.hpp"
#include "Application.hpp"

#include "LittleWooden/Input.hpp"

#include <glad/glad.h>

namespace LittleWooden {

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
			case ShaderDataType::None:		LW_CORE_ASSERT(false, "ShaderDataType::None Specified!"); return 0;
		}
		LW_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application()
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
			-0.25f, -0.25f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			 0.25f, -0.25f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,   0.4f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
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
			 0.2f,  0.6f, 0.0f,
			-0.2f,  0.6f, 0.0f,
			-0.4f,  0.0f, 0.0f,
			-0.2f, -0.6f, 0.0f,
			 0.2f, -0.6f, 0.0f
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

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
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
		// infinite loop
		while (m_Running)
		{
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw the Hex
			m_BlueShader->Bind();
			m_HexVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_HexVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			// Draw the triangle
			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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

}
