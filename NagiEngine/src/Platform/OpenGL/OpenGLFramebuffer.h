#pragma once

#include "NagiEngine/Renderer/Framebuffer.h"

namespace Nagi {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferProps& props);
		virtual ~OpenGLFramebuffer();

		void Bind() override;
		void Unbind()  override;

		ng_uint32 GetColorAttachmentRendererID() const override{ return color_attchment_id_; }
		ng_uint32 GetDepthAttachmentRendererID() const override{ return depth_attchment_id_; }

		const FramebufferProps& GetProps() const override { return props_; }

	private:
		FramebufferProps props_;
		ng_uint32 render_id_;
		ng_uint32 color_attchment_id_, depth_attchment_id_;
	};
}