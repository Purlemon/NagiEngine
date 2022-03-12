#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace PH {

	struct Renderer2DStorage
	{
		Ref<VertexArray> quad_vertex_array;
		Ref<Shader> flat_color_shader;
	};

	static Renderer2DStorage* sData;

	void Renderer2D::Init()
	{
		sData = new Renderer2DStorage();
		sData->quad_vertex_array= VertexArray::Create();

		float square_vertices[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		Ref<PH::VertexBuffer>square_vb;
		square_vb.reset(VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		square_vb->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			});
		sData->quad_vertex_array->AddVertexBuffer(square_vb);

		unsigned int square_indices[6] = { 0,1,2,2,3,0 };
		Ref<IndexBuffer>square_ib;
		square_ib.reset(IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(unsigned int)));
		sData->quad_vertex_array->SetIndexBuffer(square_ib);

		sData->flat_color_shader = Shader::Create("flat_color", "assets/shaders/vertex/flat_color.vert", "assets/shaders/fragment/flat_color.frag");
	}

	void Renderer2D::Shutdown()
	{
		delete sData;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(sData->flat_color_shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(sData->flat_color_shader)->UploadUniformMat4("u_ProjectionView", camera.GetProjectionViewMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(sData->flat_color_shader)->Bind();
		glm::mat4 transform = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0.0f)), position);
		std::dynamic_pointer_cast<OpenGLShader>(sData->flat_color_shader)->UploadUniformMat4("u_Transform", transform);
		std::dynamic_pointer_cast<OpenGLShader>(sData->flat_color_shader)->UploadUniformFloat4("u_Color", color);

		sData->quad_vertex_array->Bind();
		RenderCommand::DrawIndexed(sData->quad_vertex_array);
	}

}