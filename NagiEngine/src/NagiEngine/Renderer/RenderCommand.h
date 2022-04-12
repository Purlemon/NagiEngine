#pragma once

#include "RendererAPI.h"

namespace Nagi {

	// ÖÐ¼ä²ã
	class RenderCommand
	{
	public:
		static void Init()
		{
			renderer_api_->Init();
		}

		static void SetViewport(ph_uint32 x, ph_uint32 y, ph_uint32 width, ph_uint32 height)
		{
			return renderer_api_->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			return renderer_api_->SetClearColor(color);
		}

		static void Clear()
		{
			return renderer_api_->Clear();
		}

		static void DrawIndexed(const Nagi::Ref<VertexArray>& vertex_array, ph_uint32 count = 0)
		{ 
			return renderer_api_->DrawIndexed(vertex_array, count);
		}
	
	private:
		static RendererAPI* renderer_api_;
	};

}