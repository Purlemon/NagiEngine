#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "NagiEngine/Core/Log.h"

namespace Nagi {

	// 四边形顶点数据
	struct QuadVertex
	{
		// --------------------------
		// 一个典型的四边形顶点数据
		//           position	    |        color         | texcoord  | index | tiling
		// float square_vertices[4 * (3 + 4 + 2 + 1 + 1)] = {
		//		-1.0f, -1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,    1,     1.0f,
		//		 1.0f, -1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,    1,     1.0f,
		//		 1.0f,  1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,    1,	  1.0f,
		//		-1.0f,  1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,    1, 	  1.0f
		// };
		// --------------------------

		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texcoord;

		int tex_index;
		float tiling_factor;
	};

	// 2D渲染数据
	struct Renderer2DData
	{
		const ng_uint32 max_quads = 5000;
		const ng_uint32 max_vertices = max_quads * 4;
		const ng_uint32 max_indices = max_quads * 6;
		static const ng_uint32 max_texure_slots = 32;	// TODO：查询GPU一次支持多少个纹理单元
		
		// 四边形四个顶点的默认位置，设计成vec4是为了方便矩阵运算, 注意点的w为1
		const glm::vec4 quad_vertices[4] = {
			{ -0.5f, -0.5f, 0.0f, 1.0f },	// 左下
			{  0.5f, -0.5f, 0.0f, 1.0f },	// 右下
			{  0.5f,  0.5f, 0.0f, 1.0f },	// 右上
			{ -0.5f,  0.5f, 0.0f, 1.0f }	// 左上
		};

		// 四边形四个顶点的默认纹理坐标
		const glm::vec2 quad_texcoords[4] = {
			{ 0.0f, 0.0f },		// 左下
			{ 1.0f, 0.0f },		// 右下
			{ 1.0f, 1.0f },		// 右上
			{ 0.0f, 1.0f }		// 左上
		};

		Ref<VertexArray> quad_vertex_array;
		Ref<VertexBuffer> quad_vertex_buffer;
		Ref<Shader> texture_shader;
		Ref<Texture2D> white_texture;

		// 将分配一个QuadVertex数组，QuadVertex连续存储，用quad_vertex_buffer_ptr对每个QuadVertex操作
		ng_uint32 quad_index_count = 0;
		QuadVertex* quad_vertex_buffer_base = nullptr;	// QuadVertex数组头指针
		QuadVertex* quad_vertex_buffer_ptr = nullptr;	// 在QuadVertex数组中移动

		std::array<Ref<Texture2D>, max_texure_slots>texture_slots;	// 相当于纹理map，记录已经存在纹理单元的纹理
		ng_uint32 texture_slot_index = 1;	// 0 = white texture
	};

	static Renderer2DData sData;

	void Renderer2D::Init()
	{
		sData.quad_vertex_array= VertexArray::Create();

		sData.quad_vertex_buffer = VertexBuffer::Create(sData.max_vertices * sizeof(QuadVertex));
		sData.quad_vertex_buffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Int, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" },
			});
		sData.quad_vertex_array->AddVertexBuffer(sData.quad_vertex_buffer);

		sData.quad_vertex_buffer_base = new QuadVertex[sData.max_quads];
		// 设置顶点索引数组
		ng_uint32* quad_indices = new ng_uint32[sData.max_indices];
		ng_uint32 offset = 0;
		for (unsigned int i = 0; i < sData.max_indices; i += 6) {
			quad_indices[i + 0] = offset + 0;
			quad_indices[i + 1] = offset + 1;
			quad_indices[i + 2] = offset + 2;

			quad_indices[i + 3] = offset + 2;
			quad_indices[i + 4] = offset + 3;
			quad_indices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer>quad_ib = IndexBuffer::Create(quad_indices, sData.max_indices);
		sData.quad_vertex_array->SetIndexBuffer(quad_ib);
		delete[] quad_indices;

		// 纹理相关
		// -------------------------------
	
		// 在GPU中用0xffffffff生成一个纹理
		sData.white_texture = Texture2D::Create(1, 1);
		ng_uint32 white_texture_data = 0xffffffff; // {1.0f, 1.0f, 1.0f, 1.0f}
		sData.white_texture->SetData(&white_texture_data, sizeof(ng_uint32));

		int samplers[sData.max_texure_slots];
		for (ng_uint32 i = 0; i < sData.max_texure_slots; ++i) {
			samplers[i] = i;	// 采样器数组按顺序绑定纹理编号
		}

		sData.texture_shader = Shader::Create("texture", "assets/shaders/vertex/texture.vert", "assets/shaders/fragment/texture.frag");
		sData.texture_shader->Bind();
		sData.texture_shader->SetIntArray("u_Textures", samplers, sData.max_texure_slots);

		sData.texture_slots[0] = sData.white_texture;
	}

	void Renderer2D::Shutdown()
	{
		sData.quad_index_count = 0;
		sData.quad_vertex_buffer_ptr = sData.quad_vertex_buffer_base;

sData.texture_slot_index = 1;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		sData.texture_shader->Bind();
		sData.texture_shader->SetMat4("u_ProjectionView", camera.GetProjectionViewMatrix());

		sData.quad_index_count = 0;
		sData.quad_vertex_buffer_ptr = sData.quad_vertex_buffer_base;
	}

	void Renderer2D::EndScene()
	{
		// 计算所用的顶点数组大小
		ng_uint32 data_size = sizeof(QuadVertex) * (sData.quad_vertex_buffer_ptr - sData.quad_vertex_buffer_base);
		sData.quad_vertex_buffer->SetData(sData.quad_vertex_buffer_base, data_size);

		Flush();
	}

	void Renderer2D::Flush()
	{
		// 纹理按顺序绑定到纹理单元
		for (ng_uint32 i = 0; i < sData.texture_slot_index; ++i) {
			sData.texture_slots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(sData.quad_vertex_array, sData.quad_index_count);
	}

	void Renderer2D::DrawQuad(const QuadProps& quad_props, const glm::vec4& color)
	{
		const float tex_index = 0.0f; // White Texture
		const float tiling_factor = 1.0f;

		glm::vec3 position = glm::vec3(quad_props.position.x, quad_props.position.y, quad_props.position.z) / 100.0f;
		position.z = std::max(std::min(position.z, 1.0f), -1.0f);// z不能超过[-1,1]的NDC裁剪平面
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(quad_props.size.x, quad_props.size.y, 1.0f) / 10.0f) *
			glm::rotate(glm::mat4(1.0f), glm::radians(quad_props.rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		// 对四边形四个顶点分别设置Vertex数据
		for (ng_sizei i = 0; i < 4; ++i) {
			sData.quad_vertex_buffer_ptr->position = transform * sData.quad_vertices[i];// 在CPU内完成model矩阵的运算
			sData.quad_vertex_buffer_ptr->color = color;
			sData.quad_vertex_buffer_ptr->texcoord = sData.quad_texcoords[i];
			sData.quad_vertex_buffer_ptr->tex_index = tex_index;
			sData.quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
			++sData.quad_vertex_buffer_ptr;
		}
		// 四边形 = 两个三角形，顶点索引+6
		sData.quad_index_count += 6;
	}

	void Renderer2D::DrawQuad(const QuadProps& quad_props, const Texture2DPorps& tex2d_porps)
	{
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		glm::vec3 position = glm::vec3(quad_props.position.x, quad_props.position.y, quad_props.position.z) / 100.0f;
		position.z = std::max(std::min(position.z, 1.0f), -1.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), glm::vec3(quad_props.size.x, quad_props.size.y, 1.0f) / 10.0f) *
			glm::rotate(glm::mat4(1.0f), glm::radians(quad_props.rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		int texture_index = 0;
		// 遍历当前纹理slots，如果所需的纹理已经存在就用这个，不在就将其加入slots
		for (ng_sizei i = 1; i < sData.texture_slot_index; ++i) {
			if (*(sData.texture_slots[i].get()) == *tex2d_porps.texture.get()) {
				texture_index = i;
				break;
			}
		}
		if (texture_index == 0) {
			texture_index = sData.texture_slot_index;
			sData.texture_slots[sData.texture_slot_index] = tex2d_porps.texture;
			++sData.texture_slot_index;
		}

		for (ng_sizei i = 0; i < 4; ++i) {
			sData.quad_vertex_buffer_ptr->position = transform * sData.quad_vertices[i];
			sData.quad_vertex_buffer_ptr->color = color;
			sData.quad_vertex_buffer_ptr->texcoord = sData.quad_texcoords[i];
			sData.quad_vertex_buffer_ptr->tex_index = texture_index;
			sData.quad_vertex_buffer_ptr->tiling_factor = tex2d_porps.tiling_factor;
			++sData.quad_vertex_buffer_ptr;
		}
		sData.quad_index_count += 6;

	}
}