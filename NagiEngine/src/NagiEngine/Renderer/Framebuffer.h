#pragma once

#include "NagiEngine/Core/Core.h"
#include "NagiEngine/Core/Log.h"

namespace Nagi {

	struct FramebufferProps
	{
		ng_uint32 width, height;
		ng_uint32 samples = 1;

		bool swap_target = false;

		FramebufferProps()
			:FramebufferProps(1280,720){ }

		FramebufferProps(ng_uint32 _width,ng_uint32 _height)
			:width(_width),height(_height){ }
	};

	class Framebuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual ng_uint32 GetColorAttachmentRendererID() const = 0;
		virtual ng_uint32 GetDepthAttachmentRendererID() const = 0;

		virtual const FramebufferProps& GetProps() const = 0;

		static Ref<Framebuffer> Create(const FramebufferProps& props);

	};

}