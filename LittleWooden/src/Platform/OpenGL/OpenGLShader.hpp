#pragma once

#include "LittleWooden/Renderer/Shader.hpp"

#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace LittleWooden {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		// OpenGL Implementations of the set data
		virtual void SetInt(const std::string& name, int value) override { UploadUniformInt(name, value); }

		virtual void SetFloat(const std::string& name, float value) override { UploadUniformFloat(name, value); }
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override { UploadUniformFloat2(name, value); }
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override { UploadUniformFloat3(name, value); }
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override { UploadUniformFloat4(name, value); }

		virtual void SetMat3(const std::string& name, const glm::mat3& matrix) override { UploadUniformMat3(name, matrix); }
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) override { UploadUniformMat4(name, matrix); }

			virtual const std::string& GetName() const override { return m_Name; }

			// OpenGL specific Uniforms
			void UploadUniformInt(const std::string& name, int value);
			
			void UploadUniformFloat(const std::string& name, float value);
			void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
			void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
			void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

			void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
			void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		private:
			std::string ReadFile(const std::string& filePath);
			std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
			void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
			
		private:
			uint32_t m_RendererID;
			std::string m_Name;

		};

}
