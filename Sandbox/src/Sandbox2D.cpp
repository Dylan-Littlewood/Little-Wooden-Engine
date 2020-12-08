#include "Sandbox2D.hpp"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		:m_Name(name), m_Stopped(false), m_Func(func)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start =	std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end =		std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;

		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
	Fn m_Func;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

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
	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	// Update
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		PROFILE_SCOPE("Render::Prep");
		LittleWooden::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		LittleWooden::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Render::Draw");
		LittleWooden::Renderer2D::BeginScene(m_CameraController.GetCamera());

		LittleWooden::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
		LittleWooden::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		LittleWooden::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f, m_TintColor);
		LittleWooden::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.1f }, { 1.0f, 1.0f }, m_LogoTexture);

		LittleWooden::Renderer2D::EndScene();
	}
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

	ImGui::Begin("Profiling");
	
	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms  ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

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