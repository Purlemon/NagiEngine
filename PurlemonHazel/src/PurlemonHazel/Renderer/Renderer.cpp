#include "Renderer.h"

namespace PurlemonHazel {

	Renderer::SceneData* Renderer::scene_data_ = new SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		scene_data_->projection_view_matrix = camera.GetProjectionViewMatrix();
		// TODO: shaderʹ�ã���һ����������Ⱦ�����ʼ��
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array, const glm::mat4& transform)
	{
		shader->Bind();
		// ����Ӳ����uniform���ƣ��ǵú�shader�����ͬ��
		shader->UploadUniformMat4("u_ProjectionView", scene_data_->projection_view_matrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertex_array->Bind();
		RenderCommand::DrawIndexed(vertex_array);
	}

}