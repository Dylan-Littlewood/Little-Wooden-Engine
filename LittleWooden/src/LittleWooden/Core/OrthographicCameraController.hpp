#pragma once

#include "LittleWooden/Renderer/OrthographicCamera.hpp"
#include "LittleWooden/Core/Timestep.hpp"
#include "LittleWooden/Events/ApplicationEvent.hpp"
#include "LittleWooden/Events/MouseEvent.hpp"
#include "LittleWooden/Events/KeyEvent.hpp"


namespace LittleWooden {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnEvent(Event& e);
		void OnUpdate(Timestep ts);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_RotationEnabled;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraTranslationSpeed = 2.0f;

		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraRotationSpeed = 180.0f;
	};

}