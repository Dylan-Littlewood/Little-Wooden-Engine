#pragma once

#include "LittleWooden/Base.hpp"
#include "LittleWooden/Events/Event.hpp"
#include "LittleWooden/Core/Timestep.hpp"

namespace LittleWooden {

	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}