#include "lwpch.hpp"
#include "Texture.hpp"

#include "LittleWooden/Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace LittleWooden {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	LW_CORE_ASSERT(false, "RenderAPI::None is currentley not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(path);
		}

		LW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}