#pragma once

#include <glm/glm.hpp>

#include "PurlemonHazel/Renderer/Shader.h"

namespace PH {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertex_src, const std::string& fragment_src);
		~OpenGLShader();

		void Bind()const;
		void Unbind()const;

		void UploadUniformMat3(const char* name, const glm::mat3& matrix);
		void UploadUniformMat4(const char* name, const glm::mat4& matrix);
		
		void UploadUniforInt(const char* name, float value);

		void UploadUniforFloat(const char* name, float value);
		void UploadUniforFloat2(const char* name, const glm::vec2& vec);
		void UploadUniforFloat3(const char* name, const glm::vec3& vec);
		void UploadUniforFloat4(const char* name, const glm::vec4& vec);
	private:
		uint32_t render_id_;
	};

}