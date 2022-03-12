#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace PH {

	struct Renderer2DStorage
	{
		Ref<VertexArray> quad_vertex_array;
		Ref<Shader> texture_shader;
		Ref<Texture2D> white_texture;
	};

	static Renderer2DStorage* sData;

	void Renderer2D::Init()
	{
		sData = new Renderer2DStorage();
		sData->quad_vertex_array= VertexArray::Create();

		float square_vertices[4 * 5] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f
		};

		Ref<PH::VertexBuffer>square_vb;
		square_vb.reset(VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		square_vb->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			});
		sData->quad_vertex_array->AddVertexBuffer(square_vb);

		unsigned int square_indices[6] = { 0,1,2,2,3,0 };
		Ref<IndexBuffer>square_ib;
		square_ib.reset(IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(unsigned int)));
		sData->quad_vertex_array->SetIndexBuffer(square_ib);
	
		// 在GPU中用0xffffffff生成一个纹理
		sData->white_texture = Texture2D::Create(1, 1);
		unsigned int white_texture_data = 0xffffffff; // {1.0f, 1.0f, 1.0f, 1.0f}
		sData->white_texture->SetData(&white_texture_data, sizeof(unsigned int));

		sData->texture_shader = Shader::Create("texture", "assets/shaders/vertex/texture.vert", "assets/shaders/fragment/texture.frag");
		sData->texture_shader->Bind();
		sData->texture_shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete sData;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		sData->texture_shader->Bind();
		sData->texture_shader->SetMat4("u_ProjectionView", camera.GetProjectionViewMatrix());
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
		sData->white_texture->Bind(0);
		sData->texture_shader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		sData->texture_shader->SetMat4("u_Transform", transform);

		sData->quad_vertex_array->Bind();
		RenderCommand::DrawIndexed(sData->quad_vertex_array);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		texture->Bind(0);
		sData->texture_shader->SetFloat4("u_Color", glm::vec4(1.0f));

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));
		sData->texture_shader->SetMat4("u_Transform", transform);
		
		sData->quad_vertex_array->Bind();
		RenderCommand::DrawIndexed(sData->quad_vertex_array);
	}
}