#pragma once

#include "PurlemonHazel/Renderer/Texture.h"

namespace PH {

	class OpenGLTexture2D :public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D() override;

		inline unsigned int GetWidth()const override { return width_; }
		inline unsigned int GetHeight()const override { return height_; }

		void Bind(unsigned int slot)const override;
	private:
		std::string path_;
		unsigned int width_, height_;
		unsigned int render_id_;
	};

}