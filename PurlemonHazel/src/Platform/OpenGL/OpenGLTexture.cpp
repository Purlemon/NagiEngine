#include "OpenGLTexture.h"

#include "stb_image.h"
#include "PurlemonHazel/Core/Log.h"

namespace PH {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:path_(path), internal_format_(0), data_format_(0)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		PH_CORE_ASSERT(data, "Failed to load image!");
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

		PH_CORE_ASSERT(internal_format_ & data_format_, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &render_id_);
		glTextureStorage2D(render_id_, 1, internal_format_, width_, height_);

		glTextureParameteri(render_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(render_id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(render_id_, 0, 0, 0, width_, height_, data_format_, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(unsigned int width, unsigned int height)
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

	void OpenGLTexture2D::SetData(void* data, unsigned int size)
	{
		unsigned int byte_per_pixel = (data_format_ == GL_RGBA ? 4 : 3);
		PH_CORE_ASSERT(size == width_ * height_ * byte_per_pixel, "data必须指向全部纹理!");
		glTextureSubImage2D(render_id_, 0, 0, 0, width_, height_, data_format_, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, render_id_);
	}

}