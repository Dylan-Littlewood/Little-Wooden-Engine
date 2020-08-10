#include <LittleWooden.hpp>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.hpp"

class ExampleLayer : public LittleWooden::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_TrianglePosition(0.0f), m_QuadPosition({ -0.75f,0.0f,0.0f })
	{
		// Draw a triangle to the screen ----------------------------------------------------------------------------
		m_VertexArray.reset(LittleWooden::VertexArray::Create());

		float vertices[3 * 7] = {
			// triangle points		// Colors of points
			-0.2f, -0.2f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			 0.2f, -0.2f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.2f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};

		LittleWooden::Ref<LittleWooden::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(LittleWooden::VertexBuffer::Create(vertices, sizeof(vertices)));
		LittleWooden::BufferLayout layout = {
			{LittleWooden::ShaderDataType::Float3, "a_Position" },
			{LittleWooden::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		LittleWooden::Ref<LittleWooden::IndexBuffer> indexBuffer;
		indexBuffer.reset(LittleWooden::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Draw a triangle to the screen -----------------------------------------------------------------------

		// Draw a Quad to the screen ---------------------------------------------------------------------------
		m_QuadVertexArray.reset(LittleWooden::VertexArray::Create());

		float quadVertices[5 * 4] = {
			// Quad points
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		LittleWooden::Ref<LittleWooden::VertexBuffer> quadVB;
		quadVB.reset(LittleWooden::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));

		quadVB->SetLayout({
			{LittleWooden::ShaderDataType::Float3, "a_Position" },
			{LittleWooden::ShaderDataType::Float2, "a_TexCoord" }
		});
		
		m_QuadVertexArray->AddVertexBuffer(quadVB);

		unsigned int quadIndices[6] = { 0, 1, 2, 2, 3, 0 };
		LittleWooden::Ref<LittleWooden::IndexBuffer> quadIB;
		quadIB.reset(LittleWooden::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));
		m_QuadVertexArray->SetIndexBuffer(quadIB);
		
		// Draw a Quad to the screen ---------------------------------------------------------------------------

		// Draw a Hex to the screen ----------------------------------------------------------------------------
		
		m_HexVertexArray.reset(LittleWooden::VertexArray::Create());

		float hexVertices[3 * 6] = {
			// Hex points
			 0.0f,  0.4f, 0.0f,
			 0.35f, 0.2f, 0.0f,
			 0.35f,-0.2f, 0.0f,
			 0.0f, -0.4f, 0.0f,
			-0.35f,-0.2f, 0.0f,
			-0.35f, 0.2f, 0.0f
		};
		LittleWooden::Ref<LittleWooden::VertexBuffer> hexVB;
		hexVB.reset(LittleWooden::VertexBuffer::Create(hexVertices, sizeof(hexVertices)));

		hexVB->SetLayout({ {LittleWooden::ShaderDataType::Float3, "a_Position" } });
		m_HexVertexArray->AddVertexBuffer(hexVB);

		unsigned int hexIndices[12] = { 0, 1, 5, 1, 2, 4, 2, 3, 4, 4, 5, 1 };
		LittleWooden::Ref<LittleWooden::IndexBuffer> hexIB;
		hexIB.reset(LittleWooden::IndexBuffer::Create(hexIndices, sizeof(hexIndices) / sizeof(uint32_t)));
		m_HexVertexArray->SetIndexBuffer(hexIB);
		
		// Draw a Hex to the screen ----------------------------------------------------------------------------

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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
		
		m_Shader.reset(LittleWooden::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";


		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";
		
		m_FlatColorShader.reset(LittleWooden::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));


		m_TextureShader.reset(LittleWooden::Shader::Create("assets/shaders/Texture.glsl"));
		m_CheckerboardTexture = LittleWooden::Texture2D::Create("assets/images/Checkerboard.png");
		m_LittleWoodenLogoTexture = LittleWooden::Texture2D::Create("assets/images/Logo_Bad.png");

		std::dynamic_pointer_cast<LittleWooden::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<LittleWooden::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(LittleWooden::Timestep ts) override
	{
		// LW_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		// Camera Movement -------------------------------------------------
		if (!LittleWooden::Input::IsKeyPressed(LW_KEY_LEFT_SHIFT))
		{
			if (LittleWooden::Input::IsKeyPressed(LW_KEY_RIGHT))
				m_CameraPosition.x += m_CameraMovementSpeed * ts;
			else if (LittleWooden::Input::IsKeyPressed(LW_KEY_LEFT))
				m_CameraPosition.x -= m_CameraMovementSpeed * ts;

			if (LittleWooden::Input::IsKeyPressed(LW_KEY_UP))
				m_CameraPosition.y += m_CameraMovementSpeed * ts;
			else if (LittleWooden::Input::IsKeyPressed(LW_KEY_DOWN))
				m_CameraPosition.y -= m_CameraMovementSpeed * ts;
		}
		else if (LittleWooden::Input::IsKeyPressed(LW_KEY_LEFT_SHIFT))
		{
			if (LittleWooden::Input::IsKeyPressed(LW_KEY_RIGHT))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (LittleWooden::Input::IsKeyPressed(LW_KEY_LEFT))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		// Camera Movement -------------------------------------------------
		
		// Hex Movement ----------------------------------------------------
		if (LittleWooden::Input::IsKeyPressed(LW_KEY_D))
			m_TrianglePosition.x += m_TriangleMovementSpeed * ts;
		else if (LittleWooden::Input::IsKeyPressed(LW_KEY_A))
			m_TrianglePosition.x -= m_TriangleMovementSpeed * ts;

		if (LittleWooden::Input::IsKeyPressed(LW_KEY_W))
			m_TrianglePosition.y += m_TriangleMovementSpeed * ts;
		else if (LittleWooden::Input::IsKeyPressed(LW_KEY_S))
			m_TrianglePosition.y -= m_TriangleMovementSpeed * ts;
		// Hex Movement ----------------------------------------------------

		LittleWooden::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		LittleWooden::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		LittleWooden::Renderer::BeginScene(m_Camera);

		// --------------------------------- Render hex grid ---------------------------------
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

		std::dynamic_pointer_cast<LittleWooden::OpenGLShader>(m_FlatColorShader)->Bind();

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 pos(x * 0.15f + y % 2 * 0.075, y * 0.13f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				if(x % 2 == 0)
					std::dynamic_pointer_cast<LittleWooden::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_HexColor);
				else
					std::dynamic_pointer_cast<LittleWooden::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_HexAltColor);

				LittleWooden::Renderer::Submit(m_FlatColorShader, m_HexVertexArray, transform);
			}
		}
		// --------------------------------- Render hex grid ---------------------------------

		// --------------------------------- Render Quad -------------------------------------
		static glm::mat4 quadScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		glm::mat4 const quadPos = glm::translate(glm::mat4(1.0f), m_QuadPosition) * quadScale;

		m_CheckerboardTexture->Bind();
		LittleWooden::Renderer::Submit(m_TextureShader, m_QuadVertexArray, quadPos);

		m_LittleWoodenLogoTexture->Bind();
		LittleWooden::Renderer::Submit(m_TextureShader, m_QuadVertexArray, quadPos);
		// --------------------------------- Render Quad -------------------------------------

		// --------------------------------- Render Triangle ---------------------------------
		std::dynamic_pointer_cast<LittleWooden::OpenGLShader>(m_Shader)->Bind();
		glm::mat4 const triangleMovement = glm::translate(glm::mat4(1.0f), m_TrianglePosition) * scale;
		LittleWooden::Renderer::Submit(m_Shader, m_VertexArray, triangleMovement);
		// --------------------------------- Render Triangle ---------------------------------

		LittleWooden::Renderer::EndScene();

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Hex Color", glm::value_ptr(m_HexColor));
		ImGui::ColorEdit3("Hex Alt Color", glm::value_ptr(m_HexAltColor));

		ImGui::End();
	}

	void OnEvent(LittleWooden::Event& event) override
	{
		LittleWooden::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<LittleWooden::KeyPressedEvent>(LW_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(LittleWooden::KeyPressedEvent& event)
	{
		// TEMPORARY ------ Exit with esc key ------ TEMPORARY
		if (LittleWooden::Input::IsKeyPressed(LW_KEY_ESCAPE))
		{
			LW_INFO("Escape Key Pressed!");
			LittleWooden::Application::Get().Exit();
		}
		// TEMPORARY ------ Exit with esc key ------ TEMPORARY

		return false;
	}

private:
	LittleWooden::Ref<LittleWooden::Shader> m_Shader;
	LittleWooden::Ref<LittleWooden::Shader> m_FlatColorShader, m_TextureShader;

	LittleWooden::Ref<LittleWooden::Texture2D> m_CheckerboardTexture, m_LittleWoodenLogoTexture;

	LittleWooden::Ref<LittleWooden::VertexArray> m_VertexArray;
	LittleWooden::Ref<LittleWooden::VertexArray> m_QuadVertexArray;
	LittleWooden::Ref<LittleWooden::VertexArray> m_HexVertexArray;

	// Camera Variables -----------------------
	LittleWooden::OrthographicCamera m_Camera;
	
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	
	float m_CameraMovementSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;
	//-----------------------------------------

	glm::vec3 m_TrianglePosition;
	glm::vec3 m_QuadPosition;
	float m_TriangleMovementSpeed = 1.0f;

	glm::vec3 m_HexColor = { 0.2f, 0.5f, 0.5f };
	glm::vec3 m_HexAltColor = { 0.8f, 0.2f, 0.3f };
};

class Sandbox : public LittleWooden::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() = default;
};

LittleWooden::Application* LittleWooden::CreateApplication()
{
	return new Sandbox();
}
