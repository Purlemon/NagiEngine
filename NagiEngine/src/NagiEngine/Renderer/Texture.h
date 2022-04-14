#pragma once

#include "NagiEngine/Core/Core.h"
#include <string>

namespace Nagi {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual ng_uint32 GetWidth()const = 0;
		virtual ng_uint32 GetHeight()const = 0;
		virtual ng_uint32 GetId()const = 0;

		// 对GPU的一块内存更新
		virtual void SetData(void* data, ng_uint32 size) = 0;

		virtual void Bind(ng_uint32 slot = 0)const = 0;

		virtual bool operator==(const Texture& other)const = 0;
	};

	class Texture2D :public Texture
	{
	public:
		static Ref<Texture2D>Create(const std::string& path);
		static Ref<Texture2D>Create(ng_uint32 width, ng_uint32 height);
	};
}