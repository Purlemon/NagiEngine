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
		// TODO: shaderʹ�ã���һ����������Ⱦ�����ʼ��
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const PH::Ref<Shader>& shader, const PH::Ref<VertexArray>& vertex_array, const glm::mat4& transform)
	{
		shader->Bind();
		// ����Ӳ����uniform���ƣ��ǵú�shader�����ͬ��
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ProjectionView", scene_data_->projection_view_matrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertex_array->Bind();
		RenderCommand::DrawIndexed(vertex_array);
	}

}