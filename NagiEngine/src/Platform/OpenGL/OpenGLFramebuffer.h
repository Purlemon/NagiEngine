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

		void ResizeColorAttachment(ng_uint32 width, ng_uint32 height) override;

		ng_uint32 GetColorAttachmentRendererID() const override{ return color_attchment_id_; }
		ng_uint32 GetDepthAttachmentRendererID() const override{ return depth_attchment_id_; }

		const FramebufferProps& GetProps() const override { return props_; }

	private:
		FramebufferProps props_;
		ng_uint32 render_id_ = -1;
		ng_uint32 color_attchment_id_ = -1;
		ng_uint32 depth_attchment_id_ = -1;
	};
}