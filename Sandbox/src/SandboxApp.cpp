#include <LittleWooden.hpp>

class ExampleLayer : public LittleWooden::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		LW_INFO("ExampleLayer::Update");
	}

	void OnEvent(LittleWooden::Event& event) override
	{
		LW_TRACE("{0}", event);
	}
};

class Sandbox : public LittleWooden::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new LittleWooden::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

LittleWooden::Application* LittleWooden::CreateApplication()
{
	return new Sandbox();
}
