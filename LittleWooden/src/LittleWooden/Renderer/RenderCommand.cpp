#include "lwpch.hpp"
#include "RenderCommand.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace LittleWooden {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
