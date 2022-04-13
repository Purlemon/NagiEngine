#pragma once

#include "NagiEngine/Core/Core.h"

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Nagi {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind()const = 0;
		virtual void Unbind()const = 0;

		virtual void SetInt(const std::string& name, int val) = 0;
		virtual void SetIntArray(const std::string& name, int* vals, ng_uint32 size) = 0;
		virtual void SetFloat(const std::string& name, float val) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& val) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& val) = 0;
		virtual void SetMat3(const std::string& name, const glm::mat3& val) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& val) = 0;

		virtual const std::string& GetName()const = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertex_path, const std::string& fragment_path);
	};

	// ¥Ê¥¢“—≈‰÷√∫√µƒshader
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