#pragma once

#include"Core.h"

namespace LittleWooden {

	class LW_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT!
	Application* CreateApplication();

}
