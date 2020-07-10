#pragma once

#include "LittleWooden/Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace LittleWooden {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}