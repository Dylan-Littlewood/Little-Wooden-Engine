#include "lwpch.hpp"
#include "Shader.hpp"

#include "LittleWooden/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp"

namespace LittleWooden {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	LW_CORE_ASSERT(false, "RenderAPI::None is currentley not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		LW_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
