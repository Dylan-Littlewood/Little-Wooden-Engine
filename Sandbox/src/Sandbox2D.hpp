#pragma once

#include "LittleWooden.hpp"

class Sandbox2D : public LittleWooden::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(LittleWooden::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(LittleWooden::Event& e) override;

	bool OnKeyPressedEvent(LittleWooden::KeyPressedEvent& event);

private:
	LittleWooden::OrthographicCameraController m_CameraController;

	// Temp
	LittleWooden::Ref<LittleWooden::VertexArray> m_SquareVA;
	LittleWooden::Ref<LittleWooden::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};