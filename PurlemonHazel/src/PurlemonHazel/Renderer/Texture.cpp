#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace PH {

	Ref<Texture2D> Texture2D::Create(const std::string& path, unsigned int format)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				PH_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return std::make_shared<OpenGLTexture2D>(path, format);
			}
		}

		PH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}