#include "ngpch.h"

#include "Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include "NagiEngine/Renderer/Renderer.h"

namespace Nagi {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferProps& props)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				NAGI_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL: {
				return CreateRef<OpenGLFramebuffer>(props);
			}
		}

		NAGI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}