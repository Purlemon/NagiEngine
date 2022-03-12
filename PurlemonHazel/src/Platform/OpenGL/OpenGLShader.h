#pragma once

#include <glm/glm.hpp>

#include "PurlemonHazel/Renderer/Shader.h"

namespace PH {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertex_path, const std::string& fragment_path);
		~OpenGLShader();

		void Bind()const;
		void Unbind()const;

		const std::string& GetName()const override { return name_; }

		void UploadUniformMat3(const char* name, const glm::mat3& matrix);
		void UploadUniformMat4(const char* name, const glm::mat4& matrix);
		
		void UploadUniforInt(const char* name, float value);

		void UploadUniformFloat(const char* name, float value);
		void UploadUniformFloat2(const char* name, const glm::vec2& vec);
		void UploadUniformFloat3(const char* name, const glm::vec3& vec);
		void UploadUniformFloat4(const char* name, const glm::vec4& vec);
	private:
		void Compile(const std::string& vertex_src, const std::string& fragment_src);
		std::string ReadFile(const std::string& path);
	private:
		uint32_t render_id_;
		std::string name_;
	};

}