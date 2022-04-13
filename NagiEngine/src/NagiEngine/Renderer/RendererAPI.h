#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Nagi {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void Init() = 0;
		virtual void SetViewport(ng_uint32 x, ng_uint32 y, ng_uint32 width, ng_uint32 height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		
		virtual void DrawIndexed(const Nagi::Ref<VertexArray>& vertex_array, ng_uint32 index_count = 0) = 0;
	
		static API GetAPI() { return api_; }
	private:
		static API api_;
	};

}