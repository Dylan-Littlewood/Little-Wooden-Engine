#pragma once

#include "LittleWooden/Renderer/RenderCommand.hpp"

#include "LittleWooden/Renderer/OrthographicCamera.hpp"

#include "LittleWooden/Renderer/Shader.hpp"

namespace LittleWooden {

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ProjectionViewMatrix;
		};

		static SceneData* s_SceneData;
	};

}
