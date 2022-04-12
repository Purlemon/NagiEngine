#include "NagiEngine/Core/Core.h"

#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Nagi {

	Ref<VertexBuffer> VertexBuffer::Create(ph_uint32 size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
		{
			NAGI_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		}
		case RendererAPI::API::OpenGL:
		{
			return CreateRef<OpenGLVertexBuffer>(size);
		}
		}

		NAGI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, ph_uint32 size)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				NAGI_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
			}
		}

		NAGI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(ph_uint32* indices, ph_uint32 count)
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
			{
				NAGI_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return CreateRef<OpenGLIndexBuffer>(indices, count);
			}
		}

		NAGI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}