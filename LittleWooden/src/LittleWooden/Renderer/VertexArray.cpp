#include "lwpch.hpp"
#include "VertexArray.hpp"

#include "LittleWooden/Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace LittleWooden {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	LW_CORE_ASSERT(false, "RenderAPI::None is currentley not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		}

		LW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
}
