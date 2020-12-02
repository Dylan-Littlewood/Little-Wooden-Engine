#pragma once

#include "LittleWooden/Core/Layer.hpp"

#include "LittleWooden/Events/KeyEvent.hpp"
#include "LittleWooden/Events/MouseEvent.hpp"
#include "LittleWooden/Events/ApplicationEvent.hpp"

namespace LittleWooden {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	};

}