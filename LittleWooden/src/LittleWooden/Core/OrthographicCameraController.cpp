#include "lwpch.hpp"
#include "OrthographicCameraController.hpp"

#include "LittleWooden/Core/Input.hpp"
#include "LittleWooden/Core/KeyCodes.hpp"

namespace LittleWooden {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}
	
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(LW_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LW_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		// Camera Movement -------------------------------------------------
		if (!Input::IsKeyPressed(LW_KEY_LEFT_SHIFT))
		{
			if (Input::IsKeyPressed(LW_KEY_RIGHT))
				m_CameraPosition.x += m_CameraTranslationSpeed * ts;
			else if (Input::IsKeyPressed(LW_KEY_LEFT))
				m_CameraPosition.x -= m_CameraTranslationSpeed * ts;

			if (Input::IsKeyPressed(LW_KEY_UP))
				m_CameraPosition.y += m_CameraTranslationSpeed * ts;
			else if (Input::IsKeyPressed(LW_KEY_DOWN))
				m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(LW_KEY_LEFT_SHIFT))
		{
			if (m_Rotation)
			{
				if (Input::IsKeyPressed(LW_KEY_RIGHT))
					m_CameraRotation += m_CameraRotationSpeed * ts;
				else if (Input::IsKeyPressed(LW_KEY_LEFT))
					m_CameraRotation -= m_CameraRotationSpeed * ts;

				m_Camera.SetRotation(m_CameraRotation);
			}
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
		// Camera Movement -------------------------------------------------
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}