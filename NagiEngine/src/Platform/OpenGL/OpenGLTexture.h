#pragma once

#include "NagiEngine/Renderer/Texture.h"

#include <glad/glad.h>

namespace Nagi {

	class OpenGLTexture2D :public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(ph_uint32 width, ph_uint32 height);
		~OpenGLTexture2D() override;

		void SetData(void* data, ph_uint32 size) override;

		ph_uint32 GetWidth()const override { return width_; }
		ph_uint32 GetHeight()const override { return height_; }

		void Bind(ph_uint32 slot)const override;
	private:
		std::string path_;
		ph_uint32 width_, height_;
		ph_uint32 render_id_;
		GLenum internal_format_, data_format_;
	};

}