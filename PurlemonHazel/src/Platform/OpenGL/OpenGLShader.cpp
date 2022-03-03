#include "OpenGLShader.h"

#include "PurlemonHazel/Log.h"

#include <vector>
#include <glad/glad.h> 

#include <glm/gtc/type_ptr.hpp>

namespace PH {

	OpenGLShader::OpenGLShader(const std::string& vertex_src, const std::string& fragment_src)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertex_src.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			PH_CORE_ERROR("{0}", infoLog.data());
			PH_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragment_src.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			PH_CORE_ERROR("{0}", infoLog.data());
			PH_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		render_id_ = glCreateProgram();
		GLuint program = render_id_;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			PH_CORE_ERROR("{0}", infoLog.data());
			PH_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(render_id_);
	}

	void OpenGLShader::Bind()const
	{
		glUseProgram(render_id_);
	}
	void OpenGLShader::Unbind()const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformMat3(const char* name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(render_id_, name);
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const char* name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(render_id_, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniforFloat(const char* name, float value)
	{
		GLint location = glGetUniformLocation(render_id_, name);
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniforFloat2(const char* name, const glm::vec2& vec)
	{
		GLint location = glGetUniformLocation(render_id_, name);
		glUniform2f(location, vec.x, vec.y);
	}

	void OpenGLShader::UploadUniforFloat3(const char* name, const glm::vec3& vec)
	{
		GLint location = glGetUniformLocation(render_id_, name);
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void OpenGLShader::UploadUniforFloat4(const char* name, const glm::vec4& vec)
	{
		GLint location = glGetUniformLocation(render_id_, name);
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

}