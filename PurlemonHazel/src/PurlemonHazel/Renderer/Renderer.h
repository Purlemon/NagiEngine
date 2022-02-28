#pragma once

#include "RenderCommand.h"
#include "Shader.h"

#include "OrthographicCamera.h"

namespace PurlemonHazel {

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		// ��Ⱦÿ������
		static void Submit(
			const std::shared_ptr<Shader>& shader, 
			const std::shared_ptr<VertexArray>& vertex_array,
			const glm::mat4& transform = glm::mat4(1.0f)
		);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 projection_view_matrix;
		};

		static SceneData* scene_data_;
	};

}