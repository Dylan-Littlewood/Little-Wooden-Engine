#include "lwpch.hpp"
#include "Sandbox2D.hpp"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.hpp"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = LittleWooden::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	LittleWooden::Ref<LittleWooden::VertexBuffer> squareVB;
	squareVB.reset(LittleWooden::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ LittleWooden::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	LittleWooden::Ref<LittleWooden::IndexBuffer> squareIB;
	squareIB.reset(LittleWooden::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = LittleWooden::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(LittleWooden::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);
	
	// Render
	LittleWooden::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	LittleWooden::RenderCommand::Clear();

	LittleWooden::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<LittleWooden::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<LittleWooden::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	LittleWooden::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	LittleWooden::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Quad Color", glm::value_ptr(m_SquareColor));
	ImGui::Text("Camera Position x:%f y:%f z:%f", m_CameraController.GetCamera().GetPosition().x, m_CameraController.GetCamera().GetPosition().y, m_CameraController.GetCamera().GetPosition().z);
	ImGui::Text("Camera Rotation: %f", m_CameraController.GetCamera().GetRotation());
	ImGui::Text("Camera Zoom Level: %f", m_CameraController.GetZoomLevel());
	if (ImGui::Button("Test Button UI Event", { 200,20 }))
	{
		double mousePosX, mousePosY;
		LittleWooden::Application::GetMousePos(&mousePosX, &mousePosY);
		LittleWooden::Application::CallEvent(LittleWooden::UIClickedEvent(mousePosX, mousePosY));
	}

	ImGui::End();
}

void Sandbox2D::OnEvent(LittleWooden::Event& e)
{
	m_CameraController.OnEvent(e);

	LittleWooden::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<LittleWooden::KeyPressedEvent>(LW_BIND_EVENT_FN(Sandbox2D::OnKeyPressedEvent));
}

bool Sandbox2D::OnKeyPressedEvent(LittleWooden::KeyPressedEvent& event)
{
	if (LittleWooden::Input::IsKeyPressed(LW_KEY_ESCAPE))
	{
		LittleWooden::Application::CallEvent(LittleWooden::WindowCloseEvent());
	}
	return false;
}