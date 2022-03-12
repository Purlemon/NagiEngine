#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace PH {

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertex_path, const std::string& fragment_path)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				PH_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLShader>(name, vertex_path, fragment_path);
			}
		}

		PH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		PH_CORE_ASSERT(!Exists(name), "Shader already exists!");
		shaders_[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertex_path, const std::string& fragment_path)
	{
		auto shader = Shader::Create(name, vertex_path, fragment_path);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		PH_CORE_ASSERT(Exists(name), "Shader not be found!");
		return shaders_[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return shaders_.find(name) != shaders_.end();
	}
}