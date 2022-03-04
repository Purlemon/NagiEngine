#pragma once

#include "PurlemonHazel/Renderer/RendererAPI.h"

namespace PH {

	class OpenGLRendererAPI :public RendererAPI
	{
		void Init() override;

		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const PH::Ref<VertexArray>& vertex_array) override;
	};

}