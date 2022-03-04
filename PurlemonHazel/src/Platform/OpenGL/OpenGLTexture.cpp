#include "OpenGLTexture.h"

#include "stb_image.h"
#include "PurlemonHazel/Log.h"

#include <glad/glad.h>

namespace PH {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, unsigned int format)
		:path_(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (!data)PH_CORE_ERROR("textureŒ¥º”‘ÿ£°");
		PH_CORE_ASSERT(data, "Failed to load image!");
		width_ = width;
		height_ = height;

		glGenTextures(1, &render_id_);
		glBindTexture(GL_TEXTURE_2D, render_id_);

		glTextureParameteri(render_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(render_id_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	
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