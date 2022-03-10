#pragma once

#include "RenderCommand.h"
#include "Shader.h"

#include "OrthographicCamera.h"

namespace PH {

	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(unsigned int width, unsigned int height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		// 渲染每个物体
		static void Submit(
			const PH::Ref<Shader>& shader,
			const PH::Ref<VertexArray>& vertex_array,
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