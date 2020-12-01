#include "Sandbox2D.hpp"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = LittleWooden::Texture2D::Create("assets/images/Checkerboard.png");
	m_LogoTexture = LittleWooden::Texture2D::Create("assets/images/Logo_Good.png");
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

	LittleWooden::Renderer2D::BeginScene(m_CameraController.GetCamera());

	LittleWooden::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f, m_TintColor);
	LittleWooden::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
	LittleWooden::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
	LittleWooden::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.1f }, { 1.0f, 1.0f }, m_LogoTexture);

	LittleWooden::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Quad Color", glm::value_ptr(m_SquareColor));
	ImGui::ColorEdit4("Tint Color", glm::value_ptr(m_TintColor));
	ImGui::Text("Camera Position x:%f y:%f z:%f", m_CameraController.GetCamera().GetPosition().x, m_CameraController.GetCamera().GetPosition().y, m_CameraController.GetCamera().GetPosition().z);
	ImGui::Text("Camera Rotation: %f", m_CameraController.GetCamera().GetRotation());
	ImGui::Text("Camera Zoom Level: %f", m_CameraController.GetZoomLevel());
	if (ImGui::Button("Test Button UI Event", { 200,20 }))
	{
		double mousePosX = LittleWooden::Input::GetMouseX();
		double mousePosY = LittleWooden::Input::GetMouseY();
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