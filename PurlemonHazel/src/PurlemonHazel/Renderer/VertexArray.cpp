#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace PH {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				PH_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return std::make_shared<OpenGLVertexArray>();
			}
		}

		PH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}