#include "ngpch.h"

#include "OpenGLShader.h"

#include <glad/glad.h> 

#include <glm/gtc/type_ptr.hpp>

namespace Nagi {

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_path, const std::string& fragment_path)
		:name_(name)
	{
		std::string vertex_src = ReadFile(vertex_path);
		std::string fragment_src = ReadFile(fragment_path);
		Compile(vertex_src, fragment_src);
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

	void OpenGLShader::SetInt(const std::string& name, int val)
	{
		UploadUniformInt(name, val);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* vals, ng_uint32 size)
	{
		UploadUniformIntArray(name, vals, size);
	}

	void OpenGLShader::SetFloat(const std::string& name, float val)
	{
		UploadUniformFloat(name, val);
	}
	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& val)
	{
		UploadUniformFloat3(name, val);
	}
	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& val)
	{
		UploadUniformFloat4(name, val);
	}
	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& val)
	{
		UploadUniformMat3(name, val);
	}
	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& val)
	{
		UploadUniformMat4(name, val);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(render_id_, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(render_id_, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(render_id_, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* vals, ng_uint32 size)
	{
		GLint location = glGetUniformLocation(render_id_, name.c_str());
		glUniform1iv(location, size, vals);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(render_id_, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vec)
	{
		GLint location = glGetUniformLocation(render_id_, name.c_str());
		glUniform2f(location, vec.x, vec.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vec)
	{
		GLint location = glGetUniformLocation(render_id_, name.c_str());
		glUniform3f(location, vec.x, vec.y, vec.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vec)
	{
		GLint location = glGetUniformLocation(render_id_, name.c_str());
		glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
	}

	void OpenGLShader::Compile(const std::string& vertex_src, const std::string& fragment_src)
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

			NAGI_CORE_ERROR("{0}", infoLog.data());
			NAGI_CORE_ASSERT(false, "Vertex shader compilation failure!");
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

			NAGI_CORE_ERROR("{0}", infoLog.data());
			NAGI_CORE_ASSERT(false, "Fragment shader compilation failure!");
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

			NAGI_CORE_ERROR("{0}", infoLog.data());
			NAGI_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::string result;
		std::ifstream file;
		std::stringstream stream;

		file.open(path);

		if (file) {
			stream << file.rdbuf();
			file.close();
			result = stream.str();
		}
		else {
			NAGI_CORE_ERROR("Vertex shader file could not open in [{0}]", path);
		}
		return result;
	}
}