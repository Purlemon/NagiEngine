#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace PH {

	Renderer::SceneData* Renderer::scene_data_ = new SceneData();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		scene_data_->projection_view_matrix = camera.GetProjectionViewMatrix();
		// TODO: shader使用，归一化，各种渲染矩阵初始化
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const PH::Ref<Shader>& shader, const PH::Ref<VertexArray>& vertex_array, const glm::mat4& transform)
	{
		shader->Bind();
		// 这里硬编码uniform名称，记得和shader里面的同名
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ProjectionView", scene_data_->projection_view_matrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertex_array->Bind();
		RenderCommand::DrawIndexed(vertex_array);
	}

}