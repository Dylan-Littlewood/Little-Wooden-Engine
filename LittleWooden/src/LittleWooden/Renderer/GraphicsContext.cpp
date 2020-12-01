#include "lwpch.hpp"
#include "GraphicsContext.hpp"

#include "LittleWooden/Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLContext.hpp"

namespace LittleWooden {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	LW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		LW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}