#include "ngpch.h"

#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Nagi {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:path_(path), internal_format_(0), data_format_(0)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		NAGI_CORE_ASSERT(data, "Failed to load image!");
		width_ = width;
		height_ = height;

		if (channels == 3) {	// RGB
			internal_format_ = GL_RGB32F;
			data_format_ = GL_RGB;
		}
		else if (channels == 4) { //RGBA
			internal_format_ = GL_RGBA32F;
			data_format_ = GL_RGBA;
		}

		NAGI_CORE_ASSERT(internal_format_ & data_format_, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &render_id_);
		glTextureStorage2D(render_id_, 1, internal_format_, width_, height_);

		glTextureParameteri(render_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(render_id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(render_id_, 0, 0, 0, width_, height_, data_format_, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(ng_uint32 width, ng_uint32 height)
		:width_(width),height_(height)
	{
		internal_format_ = GL_RGBA8;
		data_format_ = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &render_id_);
		glTextureStorage2D(render_id_, 1, internal_format_, width_, height_);

		glTextureParameteri(render_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(render_id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(render_id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(render_id_, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &render_id_);
	}

	void OpenGLTexture2D::SetData(void* data, ng_uint32 size)
	{
		ng_uint32 byte_per_pixel = (data_format_ == GL_RGBA ? 4 : 3);
		NAGI_CORE_ASSERT(size == width_ * height_ * byte_per_pixel, "data必须指向全部纹理!");
		glTextureSubImage2D(render_id_, 0, 0, 0, width_, height_, data_format_, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(ng_uint32 slot) const
	{
		// 将纹理绑定到指定的(slot)纹理单元
		glBindTextureUnit(slot, render_id_);
	}

}