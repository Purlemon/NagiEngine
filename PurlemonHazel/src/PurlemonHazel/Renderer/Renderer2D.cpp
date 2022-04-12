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
		square_vb = VertexBuffer::Create(square_vertices, sizeof(square_vertices));
		square_vb->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			});
		sData->quad_vertex_array->AddVertexBuffer(square_vb);

		ph_uint32 square_indices[6] = { 0,1,2,2,3,0 };
		Ref<IndexBuffer>square_ib;
		square_ib = IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(ph_uint32));
		sData->quad_vertex_array->SetIndexBuffer(square_ib);
	
		// 在GPU中用0xffffffff生成一个纹理
		sData->white_texture = Texture2D::Create(1, 1);
		ph_uint32 white_texture_data = 0xffffffff; // {1.0f, 1.0f, 1.0f, 1.0f}
		sData->white_texture->SetData(&white_texture_data, sizeof(ph_uint32));

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

	void Renderer2D::DrawQuad(const QuadProps& quad_props, const glm::vec4& color)
	{
		sData->white_texture->Bind(0);
		sData->texture_shader->SetFloat4("u_Color", color);
		sData->texture_shader->SetFloat("u_TilingFactor", 1.0f);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), quad_props.position / 100.0f) *
			glm::scale(glm::mat4(1.0f), glm::vec3(quad_props.size.x, quad_props.size.y, 1.0f) / 10.0f) *
			glm::rotate(glm::mat4(1.0f), glm::radians(quad_props.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		sData->texture_shader->SetMat4("u_Transform", transform);

		sData->quad_vertex_array->Bind();
		RenderCommand::DrawIndexed(sData->quad_vertex_array);
	}


	void Renderer2D::DrawQuad(const QuadProps& quad_props, const Texture2DPorps& tex2d_porps)
	{
		tex2d_porps.texture->Bind(0);
		sData->texture_shader->SetFloat4("u_Color", tex2d_porps.tintcolor);
		sData->texture_shader->SetFloat("u_TilingFactor", tex2d_porps.tiling_factor);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), quad_props.position / 100.0f) *
			glm::scale(glm::mat4(1.0f), glm::vec3(quad_props.size.x, quad_props.size.y, 1.0f) / 10.0f) *
			glm::rotate(glm::mat4(1.0f), glm::radians(quad_props.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		sData->texture_shader->SetMat4("u_Transform", transform);
		
		sData->quad_vertex_array->Bind();
		RenderCommand::DrawIndexed(sData->quad_vertex_array);
	}
}