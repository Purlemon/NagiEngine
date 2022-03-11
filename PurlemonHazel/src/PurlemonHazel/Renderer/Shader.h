#pragma once

#include <string>
#include <unordered_map>

#include <PurlemonHazel/Core/Core.h>

namespace PH {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind()const = 0;
		virtual void Unbind()const = 0;

		virtual const std::string& GetName()const = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertex_path, const std::string& fragment_path);
	};

	// �洢�����úõ�shader
	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		Ref<Shader>Load(const std::string& name, const std::string& vertex_path, const std::string& fragment_path);
		
		Ref<Shader>Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>>shaders_;
	};
}