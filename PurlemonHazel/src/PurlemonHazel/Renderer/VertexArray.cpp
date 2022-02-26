#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace PurlemonHazel {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
		{
			PH_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		}
		case RendererAPI::OpenGL:
		{
			return new OpenGLVertexArray();
		}
		}

		PH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}