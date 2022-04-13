#pragma once

#include "NagiEngine/Renderer/RendererAPI.h"

namespace Nagi {

	class OpenGLRendererAPI :public RendererAPI
	{
		void Init() override;

		void SetViewport(ng_uint32 x, ng_uint32 y, ng_uint32 width, ng_uint32 height) override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const Nagi::Ref<VertexArray>& vertex_array, ng_uint32 index_count = 0) override;
	};

}