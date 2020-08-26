#include "lwpch.hpp"
#include "OpenGLContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LittleWooden {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LW_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LW_CORE_ASSERT(status, "Failed to initialize Glad!");

		LW_CORE_INFO("OpenGL Info:----------------------------");
		LW_CORE_INFO("   Vendor: {0}", glGetString(GL_VENDOR));
		LW_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		LW_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

#ifdef LW_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		LW_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "LittleWooden requires at least OpenGL version 4.5!");
#endif
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}