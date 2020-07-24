#include <LittleWooden.hpp>

#include <imgui/imgui.h>

class ExampleLayer : public LittleWooden::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		// Draw a triangle to the screen
		m_VertexArray.reset(LittleWooden::VertexArray::Create());

		float vertices[3 * 7] = {
			// triangle points		// Colors of points
			-0.2f, -0.2f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			 0.2f, -0.2f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.2f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<LittleWooden::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(LittleWooden::VertexBuffer::Create(vertices, sizeof(vertices)));
		LittleWooden::BufferLayout layout = {
			{LittleWooden::ShaderDataType::Float3, "a_Position" },
			{LittleWooden::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<LittleWooden::IndexBuffer> indexBuffer;
		indexBuffer.reset(LittleWooden::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_HexVertexArray.reset(LittleWooden::VertexArray::Create());

		float hexVertices[3 * 6] = {
			// Hex points
			 0.4f,  0.0f, 0.0f,
			 0.2f,  0.35f, 0.0f,
			-0.2f,  0.35f, 0.0f,
			-0.4f,  0.0f, 0.0f,
			-0.2f, -0.35f, 0.0f,
			 0.2f, -0.35f, 0.0f
		};
		std::shared_ptr<LittleWooden::VertexBuffer> hexVB;
		hexVB.reset(LittleWooden::VertexBuffer::Create(hexVertices, sizeof(hexVertices)));

		hexVB->SetLayout({ {LittleWooden::ShaderDataType::Float3, "a_Position" } });
		m_HexVertexArray->AddVertexBuffer(hexVB);

		unsigned int hexIndices[12] = { 0, 1, 5, 1, 2, 4, 2, 3, 4, 4, 5, 1 };
		std::shared_ptr<LittleWooden::IndexBuffer> hexIB;
		hexIB.reset(LittleWooden::IndexBuffer::Create(hexIndices, sizeof(hexIndices) / sizeof(uint32_t)));
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


		m_Shader.reset(new LittleWooden::Shader(vertexSrc, fragmentSrc));
		m_BlueShader.reset(new LittleWooden::Shader(tealShaderVertexSrc, tealShaderFragmentSrc));

	}

	void OnUpdate() override
	{
		// Camera Movement -------------------------------------------------
		if (!LittleWooden::Input::IsKeyPressed(LW_KEY_LEFT_SHIFT))
		{
			if (LittleWooden::Input::IsKeyPressed(LW_KEY_RIGHT))
				m_CameraPosition.x += m_CameraMovementSpeed;
			else if (LittleWooden::Input::IsKeyPressed(LW_KEY_LEFT))
				m_CameraPosition.x -= m_CameraMovementSpeed;

			if (LittleWooden::Input::IsKeyPressed(LW_KEY_UP))
				m_CameraPosition.y += m_CameraMovementSpeed;
			else if (LittleWooden::Input::IsKeyPressed(LW_KEY_DOWN))
				m_CameraPosition.y -= m_CameraMovementSpeed;
		}
		else if (LittleWooden::Input::IsKeyPressed(LW_KEY_LEFT_SHIFT))
		{
			if (LittleWooden::Input::IsKeyPressed(LW_KEY_RIGHT))
				m_CameraRotation += m_CameraRotationSpeed;
			else if (LittleWooden::Input::IsKeyPressed(LW_KEY_LEFT))
				m_CameraRotation -= m_CameraRotationSpeed;
		}
		// Camera Movement -------------------------------------------------

		LittleWooden::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		LittleWooden::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		LittleWooden::Renderer::BeginScene(m_Camera);

		LittleWooden::Renderer::Submit(m_BlueShader, m_HexVertexArray);
		LittleWooden::Renderer::Submit(m_Shader, m_VertexArray);

		LittleWooden::Renderer::EndScene();
		
	}

	void OnImGuiRender() override
	{
		
	}

	void OnEvent(LittleWooden::Event& event) override
	{
		LittleWooden::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<LittleWooden::KeyPressedEvent>(LW_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(LittleWooden::KeyPressedEvent& event)
	{
		return false;
	}
private:
	std::shared_ptr<LittleWooden::Shader> m_BlueShader;
	std::shared_ptr<LittleWooden::Shader> m_Shader;

	std::shared_ptr<LittleWooden::VertexArray> m_VertexArray;
	std::shared_ptr<LittleWooden::VertexArray> m_HexVertexArray;

	// Camera Variables -----------------------
	LittleWooden::OrthographicCamera m_Camera;
	
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	
	float m_CameraMovementSpeed = 0.1f;
	float m_CameraRotationSpeed = 1.0f;
	//-----------------------------------------
};

class Sandbox : public LittleWooden::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

LittleWooden::Application* LittleWooden::CreateApplication()
{
	return new Sandbox();
}
