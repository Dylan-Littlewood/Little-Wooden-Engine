#include <LittleWooden.hpp>

#include <imgui/imgui.h>

class ExampleLayer : public LittleWooden::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (LittleWooden::Input::IsKeyPressed(LW_KEY_ENTER))
			LW_INFO(" Poll: The Enter Key Was Pressed!");
	}

//	void OnImGuiRender() override
//	{
//		ImGui::Begin("Test");
//		ImGui::Text("Hello World!");
//		ImGui::End();
//	}

	void OnEvent(LittleWooden::Event& event) override
	{
		if (event.GetEventType() == LittleWooden::EventType::KeyPressed)
		{
			LittleWooden::KeyPressedEvent& e = (LittleWooden::KeyPressedEvent&)event;
			if ( e.GetKeyCode() == LW_KEY_ENTER)
				LW_INFO("Event: The Enter Key Was Pressed!");
			LW_TRACE("{0}", (char)e.GetKeyCode());
		}
		//LW_TRACE("{0}", event);
	}
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
