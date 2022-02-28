#include "Renderer.h"

namespace PurlemonHazel {

	Renderer::SceneData* Renderer::scene_data_ = new SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		scene_data_->projection_view_matrix = camera.GetProjectionViewMatrix();
		// TODO: shader使用，归一化，各种渲染矩阵初始化
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array, const glm::mat4& transform)
	{
		shader->Bind();
		// 这里硬编码uniform名称，记得和shader里面的同名
		shader->UploadUniformMat4("u_ProjectionView", scene_data_->projection_view_matrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertex_array->Bind();
		RenderCommand::DrawIndexed(vertex_array);
	}

}