#include "lwpch.hpp"
#include "RendererUI.hpp"


#include "LittleWooden/Renderer/RenderCommand.hpp"
#include "LittleWooden/Renderer/VertexArray.hpp"
#include "LittleWooden/Renderer/Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace LittleWooden {

	struct RendererUIStorage
	{
		Ref<VertexArray> UIVertexArray;
		Ref<Shader> UIShader;
	};

	static RendererUIStorage* s_Data;

	void RendererUI::Init()
	{
		s_Data = new RendererUIStorage;
		s_Data->UIVertexArray = VertexArray::Create();

		float uiVertices[5 * 4] = {
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f
		};

		Ref<VertexBuffer> uiVB;
		uiVB.reset(VertexBuffer::Create(uiVertices, sizeof(uiVertices)));
		uiVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		s_Data->UIVertexArray->AddVertexBuffer(uiVB);

		uint32_t uiIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> uiIB;
		uiIB.reset(IndexBuffer::Create(uiIndices, sizeof(uiIndices) / sizeof(uint32_t)));
		s_Data->UIVertexArray->SetIndexBuffer(uiIB);

		s_Data->UIShader = Shader::Create("assets/shaders/UIShader.glsl");
	}

	void RendererUI::Shutdown()
	{
		delete s_Data;
	}

	void RendererUI::BeginScene()
	{
		s_Data->UIShader->Bind();
		s_Data->UIShader->SetFloat2("u_Screen", { 1280.0f, 720.0f });
	}

	void RendererUI::EndScene()
	{

	}

	void RendererUI::DrawElement(const glm::vec2& position, const glm::vec2& size, const glm::vec4& borderRadius, const glm::vec4& color)
	{
		s_Data->UIShader->Bind();
		s_Data->UIShader->SetFloat2("u_Size", size);
		s_Data->UIShader->SetFloat4("u_Color", color);
		s_Data->UIShader->SetFloat2("u_Offset", position);
		s_Data->UIShader->SetFloat4("u_BorderRadius", borderRadius);
		//                                               TLr    TRr    BRr    BLr

		s_Data->UIVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->UIVertexArray);
	}

}
