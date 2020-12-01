#include "lwpch.hpp"
#include "RenderCommand.hpp"


namespace LittleWooden {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
