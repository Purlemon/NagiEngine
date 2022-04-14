#pragma once

#include "NagiEngine/Renderer/Texture.h"

#include <glad/glad.h>

namespace Nagi {

	class OpenGLTexture2D :public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(ng_uint32 width, ng_uint32 height);
		~OpenGLTexture2D() override;

		void SetData(void* data, ng_uint32 size) override;

		ng_uint32 GetWidth()const override { return width_; }
		ng_uint32 GetHeight()const override { return height_; }
		ng_uint32 GetId()const override { return render_id_; }

		void Bind(ng_uint32 slot)const override;

		bool operator==(const Texture& other)const override
		{
			return render_id_ == ((OpenGLTexture2D&)(other)).render_id_;
		}
	private:
		std::string path_;
		ng_uint32 width_, height_;
		ng_uint32 render_id_;
		GLenum internal_format_, data_format_;
	};

}