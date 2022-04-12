#pragma once

#include "NagiEngine/Renderer/RendererAPI.h"

namespace Nagi {

	class OpenGLRendererAPI :public RendererAPI
	{
		void Init() override;

		void SetViewport(ph_uint32 x, ph_uint32 y, ph_uint32 width, ph_uint32 height) override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const Nagi::Ref<VertexArray>& vertex_array, ph_uint32 index_count = 0) override;
	};

}