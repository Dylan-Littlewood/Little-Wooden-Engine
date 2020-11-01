#pragma once
#include "Event.hpp"

namespace LittleWooden {

	class UIClickedEvent : public Event
	{
	public:
		UIClickedEvent(double mouseX, double mouseY)
			: m_MouseX(mouseX), m_MouseY(mouseY) {}

		inline double GetX() const { return m_MouseX; }
		inline double GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "UIClickedEvent: MousePosX " << m_MouseX << ", MousePosY " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(UIClicked)
			EVENT_CLASS_CATEGORY(EventCategoryUI | EventCategoryInput)
	private:
		double m_MouseX, m_MouseY;
	};

}