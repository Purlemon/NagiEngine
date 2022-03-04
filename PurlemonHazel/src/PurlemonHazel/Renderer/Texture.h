#pragma once

#include "PurlemonHazel/Core.h"
#include <string>

namespace PH {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual unsigned int GetWidth()const = 0;
		virtual unsigned int GetHeight()const = 0;

		virtual void Bind(unsigned int slot = 0)const = 0;
	};

	class Texture2D :public Texture
	{
	public:
		static Ref<Texture2D>Create(const std::string& path);
	};
}