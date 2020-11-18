#pragma once

#include"LittleWooden/Renderer/OrthographicCamera.hpp"

namespace LittleWooden {

	class RendererUI
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene();
		static void EndScene();

		// Primitives
		static void DrawElement(const glm::vec2& position, const glm::vec2& size, const glm::vec4& borderRadius, const glm::vec4& color);

	};

}