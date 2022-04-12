#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace PH {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				PH_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLTexture2D>(path);
			}
		}

		PH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(ph_uint32 width, ph_uint32 height)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				PH_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLTexture2D>(width, height);
			}
		}

		PH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}