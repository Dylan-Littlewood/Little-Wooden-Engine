#include "lwpch.hpp"
#include "Buffer.hpp"

#include "Renderer.hpp"

#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace LittleWooden {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		LW_CORE_ASSERT(false, "RenderAPI::None is currentley not supported!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		LW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		LW_CORE_ASSERT(false, "RenderAPI::None is currentley not supported!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, size);
		}

		LW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}