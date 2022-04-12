#pragma once

#include "PurlemonHazel/Core/Core.h"
#include <string>

namespace PH {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual ph_uint32 GetWidth()const = 0;
		virtual ph_uint32 GetHeight()const = 0;

		// 对GPU的一块内存更新
		virtual void SetData(void* data, ph_uint32 size) = 0;

		virtual void Bind(ph_uint32 slot = 0)const = 0;
	};

	class Texture2D :public Texture
	{
	public:
		static Ref<Texture2D>Create(const std::string& path);
		static Ref<Texture2D>Create(ph_uint32 width, ph_uint32 height);
	};
}