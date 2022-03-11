#include "OpenGLTexture.h"

#include "stb_image.h"
#include "PurlemonHazel/Core/Log.h"

#include <glad/glad.h>

namespace PH {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:path_(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		PH_CORE_ASSERT(data, "Failed to load image!");
		width_ = width;
		height_ = height;

		GLenum internal_format = 0, data_format = 0;
		if (channels == 3) {	// RGB
			internal_format = GL_RGB32F;
			data_format = GL_RGB;
		}
		else if (channels == 4) { //RGBA
			internal_format = GL_RGBA32F;
			data_format = GL_RGBA;
		}

		PH_CORE_ASSERT(internal_format & data_format, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &render_id_);
		glTextureStorage2D(render_id_, 1, internal_format, width_, height_);

		glTextureParameteri(render_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(render_id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(render_id_, 0, 0, 0, width_, height_, data_format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &render_id_);
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, render_id_);
	}

}