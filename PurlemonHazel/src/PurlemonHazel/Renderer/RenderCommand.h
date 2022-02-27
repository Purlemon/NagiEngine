#pragma once

#include "RendererAPI.h"

namespace PurlemonHazel {

	// ÖÐ¼ä²ã
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			return renderer_api_->SetClearColor(color);
		}

		inline static void Clear()
		{
			return renderer_api_->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) 
		{ 
			return renderer_api_->DrawIndexed(vertex_array); 
		}
	
	private:
		static RendererAPI* renderer_api_;
	};

}