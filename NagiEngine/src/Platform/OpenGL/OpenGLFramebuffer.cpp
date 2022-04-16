#include "OpenGLFramebuffer.h"

#include "glad/glad.h"

namespace Nagi {

	static const ng_uint32 kMaxFramebufferSize = 8192;

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferProps& props)
		:props_(props)
	{
		// 创建绑定FBO
		glCreateFramebuffers(1, &render_id_);
		glBindFramebuffer(GL_FRAMEBUFFER, render_id_);

		// 创建Texture2D作为Framebuffer的颜色缓冲(out image)
		glCreateTextures(GL_TEXTURE_2D, 1, &color_attchment_id_);
		glBindTexture(GL_TEXTURE_2D, color_attchment_id_);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, props.width, props.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attchment_id_, 0);

		// 创建Texture2D作为Framebuffer的深度缓冲
		glCreateTextures(GL_TEXTURE_2D, 1, &depth_attchment_id_);
		glBindTexture(GL_TEXTURE_2D, depth_attchment_id_);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, props.width, props.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_attchment_id_, 0);

		NAGI_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &render_id_);
		glDeleteTextures(1, &color_attchment_id_);
		glDeleteTextures(1, &depth_attchment_id_);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, render_id_);
		glViewport(0, 0, props_.width, props_.height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::ResizeColorAttachment(ng_uint32 width, ng_uint32 height) 
	{
		if (width == 0 || height == 0 || width > kMaxFramebufferSize || height > kMaxFramebufferSize) {
			NAGI_CORE_WARN("Try to resize framebuffer to ({0}, {1})", width, height);
			return;
		}

		if (render_id_ != -1) {
			props_.width = width;
			props_.height = height;

			glBindTexture(GL_TEXTURE_2D, color_attchment_id_);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			glBindTexture(GL_TEXTURE_2D, depth_attchment_id_);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		}
	}

}