#pragma once

#include "LittleWooden/Renderer/RenderCommand.hpp"
#include "LittleWooden/Renderer/OrthographicCamera.hpp"
#include "LittleWooden/Renderer/Shader.hpp"

namespace LittleWooden {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ProjectionViewMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};

}
