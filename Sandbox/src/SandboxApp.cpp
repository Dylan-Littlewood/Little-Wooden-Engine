#include <LittleWooden.hpp>
#include <LittleWooden/Core/EntryPoint.hpp>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.hpp"

class ExampleLayer : public LittleWooden::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true), m_TrianglePosition(0.0f), m_QuadPosition({ -0.75f,0.0f,0.0f })
	{
		// Draw a triangle to the screen ----------------------------------------------------------------------------
		m_VertexArray = LittleWooden::VertexArray::Create();

		float vertices[3 * 7] = {
			// triangle points		// Colors of points
			-0.2f, -0.2f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			 0.2f, -0.2f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.2f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};

		LittleWooden::Ref<LittleWooden::VertexBuffer> vertexBuffer = LittleWooden::VertexBuffer::Create(vertices, sizeof(vertices));
		LittleWooden::BufferLayout layout = {
			{LittleWooden::ShaderDataType::Float3, "a_Position" },
			{LittleWooden::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		LittleWooden::Ref<LittleWooden::IndexBuffer> indexBuffer = LittleWooden::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Draw a triangle to the screen -----------------------------------------------------------------------

		// Draw a Quad to the screen ---------------------------------------------------------------------------
		m_QuadVertexArray = LittleWooden::VertexArray::Create();

		float quadVertices[5 * 4] = {
			// Quad points
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		LittleWooden::Ref<LittleWooden::VertexBuffer> quadVB = LittleWooden::VertexBuffer::Create(quadVertices, sizeof(quadVertices));

		quadVB->SetLayout({
			{LittleWooden::ShaderDataType::Float3, "a_Position" },
			{LittleWooden::ShaderDataType::Float2, "a_TexCoord" }
		});
		
		m_QuadVertexArray->AddVertexBuffer(quadVB);

		unsigned int quadIndices[6] = { 0, 1, 2, 2, 3, 0 };
		LittleWooden::Ref<LittleWooden::IndexBuffer> quadIB = LittleWooden::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
		m_QuadVertexArray->SetIndexBuffer(quadIB);
		
		// Draw a Quad to the screen ---------------------------------------------------------------------------

		// Draw a Hex to the screen ----------------------------------------------------------------------------
		
		m_HexVertexArray = LittleWooden::VertexArray::Create();

		float hexVertices[3 * 6] = {
			// Hex points
			 0.0f,  0.4f, 0.0f,
			 0.35f, 0.2f, 0.0f,
			 0.35f,-0.2f, 0.0f,
			 0.0f, -0.4f, 0.0f,
			-0.35f,-0.2f, 0.0f,
			-0.35f, 0.2f, 0.0f
		};
		LittleWooden::Ref<LittleWooden::VertexBuffer> hexVB = LittleWooden::VertexBuffer::Create(hexVertices, sizeof(hexVertices));

		hexVB->SetLayout({ {LittleWooden::ShaderDataType::Float3, "a_Position" } });
		m_HexVertexArray->AddVertexBuffer(hexVB);

		unsigned int hexIndices[12] = { 0, 1, 5, 1, 2, 4, 2, 3, 4, 4, 5, 1 };
		LittleWooden::Ref<LittleWooden::IndexBuffer> hexIB = LittleWooden::IndexBuffer::Create(hexIndices, sizeof(hexIndices) / sizeof(uint32_t));
		m_HexVertexArray->SetIndexBuffer(hexIB);
		
		// Draw a Hex to the screen ----------------------------------------------------------------------------

		//m_Shader = LittleWooden::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);
		//m_FlatColorShader = LittleWooden::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);


		auto positionColorShader = m_ShaderLibrary.Load("assets/shaders/PositionColor.glsl");
		positionColorShader->Bind();
		auto flatColorShader = m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");
		flatColorShader->Bind();

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_CheckerboardTexture = LittleWooden::Texture2D::Create("assets/images/Checkerboard.png");
		m_LittleWoodenLogoTexture = LittleWooden::Texture2D::Create("assets/images/Logo_Good.png");

		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);



	}

	void OnUpdate(LittleWooden::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render

		// LW_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

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

		LittleWooden::Renderer::BeginScene(m_CameraController.GetCamera());

		// --------------------------------- Render hex grid ---------------------------------
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

		auto flatColorShader = m_ShaderLibrary.Get("FlatColor");

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 pos(x * 0.15f + y % 2 * 0.075, y * 0.13f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				if(x % 2 == 0)
					flatColorShader->SetFloat3("u_Color", m_HexColor);
				else
					flatColorShader->SetFloat3("u_Color", m_HexAltColor);

				LittleWooden::Renderer::Submit(flatColorShader, m_HexVertexArray, transform);
			}
		}
		// --------------------------------- Render hex grid ---------------------------------

		// --------------------------------- Render Quad -------------------------------------
		static glm::mat4 quadScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		glm::mat4 const quadPos = glm::translate(glm::mat4(1.0f), m_QuadPosition) * quadScale;

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_CheckerboardTexture->Bind();
		LittleWooden::Renderer::Submit(textureShader, m_QuadVertexArray, quadPos);

		m_LittleWoodenLogoTexture->Bind();
		LittleWooden::Renderer::Submit(textureShader, m_QuadVertexArray, quadPos);
		// --------------------------------- Render Quad -------------------------------------

		// --------------------------------- Render Triangle ---------------------------------
		auto positionColorShader = m_ShaderLibrary.Get("PositionColor");

		glm::mat4 const triangleMovement = glm::translate(glm::mat4(1.0f), m_TrianglePosition) * scale;
		LittleWooden::Renderer::Submit(positionColorShader, m_VertexArray, triangleMovement);
		// --------------------------------- Render Triangle ---------------------------------

		LittleWooden::Renderer::EndScene();

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");

		ImGui::ColorEdit3("Hex Color", glm::value_ptr(m_HexColor));
		ImGui::ColorEdit3("Hex Alt Color", glm::value_ptr(m_HexAltColor));
		ImGui::Text("Camera Position x:%f y:%f z:%f", m_CameraController.GetCamera().GetPosition().x, m_CameraController.GetCamera().GetPosition().y, m_CameraController.GetCamera().GetPosition().z);
		ImGui::Text("Camera Rotation: %f", m_CameraController.GetCamera().GetRotation());
		ImGui::Text("Camera Zoom Level: %f", m_CameraController.GetZoomLevel());

		ImGui::End();
	}

	void OnEvent(LittleWooden::Event& e) override
	{
		m_CameraController.OnEvent(e);

		LittleWooden::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<LittleWooden::KeyPressedEvent>(LW_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(LittleWooden::KeyPressedEvent& event)
	{
		// TEMPORARY ------ Exit with esc key ------ TEMPORARY
		if (LittleWooden::Input::IsKeyPressed(LW_KEY_ESCAPE))
		{
			LW_INFO("Escape Key Pressed!");
			LittleWooden::Application::CallEvent(LittleWooden::WindowCloseEvent());
		}
		// TEMPORARY ------ Exit with esc key ------ TEMPORARY

		return false;
	}

private:
	LittleWooden::ShaderLibrary m_ShaderLibrary;

	LittleWooden::Ref<LittleWooden::Texture2D> m_CheckerboardTexture, m_LittleWoodenLogoTexture;

	LittleWooden::Ref<LittleWooden::VertexArray> m_VertexArray;
	LittleWooden::Ref<LittleWooden::VertexArray> m_QuadVertexArray;
	LittleWooden::Ref<LittleWooden::VertexArray> m_HexVertexArray;

	// Camera Variables -----------------------
	LittleWooden::OrthographicCameraController m_CameraController;
	
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
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() = default;
};

LittleWooden::Application* LittleWooden::CreateApplication()
{
	return new Sandbox();
}
