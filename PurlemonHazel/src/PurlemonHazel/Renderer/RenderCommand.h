#pragma once

#include "RendererAPI.h"

namespace PH {

	// ÖÐ¼ä²ã
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			renderer_api_->Init();
		}

		inline static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
		{
			return renderer_api_->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			return renderer_api_->SetClearColor(color);
		}

		inline static void Clear()
		{
			return renderer_api_->Clear();
		}

		inline static void DrawIndexed(const PH::Ref<VertexArray>& vertex_array)
		{ 
			return renderer_api_->DrawIndexed(vertex_array); 
		}
	
	private:
		static RendererAPI* renderer_api_;
	};

}