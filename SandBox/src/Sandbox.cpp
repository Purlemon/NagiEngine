#include<PurlemonHazel.h>

#include "imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public PH::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), camera_(-1.6f, 1.6f, -0.9f, 0.9f), camera_pos_(0.0f), camera_rotation_(0.0f), square_pos_(0.0f)
	{

		// ----------------------------
		// OpenGL Render
		// ----------------------------

		// 三角形
		vertex_array_.reset(PH::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		PH::BufferLayout layout = {
			{PH::ShaderDataType::Float3, "a_Position"},
			{PH::ShaderDataType::Float4, "a_Color"},
		};
		PH::Ref<PH::VertexBuffer>vertex_buffer_;
		vertex_buffer_.reset(PH::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertex_buffer_->SetLayout(layout);
		vertex_array_->AddVertexBuffer(vertex_buffer_);

		unsigned int indices[3] = { 0,1,2 };
		PH::Ref<PH::IndexBuffer>index_buffer_;
		index_buffer_.reset(PH::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		vertex_array_->SetIndexBuffer(index_buffer_);

		std::string vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ProjectionView;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragment_src = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		shader_.reset(PH::Shader::Create(vertex_src, fragment_src));

		// 正方形
		square_va_.reset(PH::VertexArray::Create());

		float square_vertices[5 * 4] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f,
		};

		PH::Ref<PH::VertexBuffer>square_vb;
		square_vb.reset(PH::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		square_vb->SetLayout({
			{ PH::ShaderDataType::Float3, "a_Position" },
			{ PH::ShaderDataType::Float2, "a_Position" }
			});
		square_va_->AddVertexBuffer(square_vb);

		unsigned int square_indices[6] = { 0,1,2,2,3,0 };
		PH::Ref<PH::IndexBuffer>square_ib;
		square_ib.reset(PH::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(unsigned int)));
		square_va_->SetIndexBuffer(square_ib);

		std::string blue_vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ProjectionView;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string blue_fragment_src = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			in vec3 v_Position;

			void main()
			{
				color = u_Color;
			}
		)";
		color_shader_.reset(PH::Shader::Create(blue_vertex_src, blue_fragment_src));
	
		std::string tex_vertex_src = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ProjectionView;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ProjectionView * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string tex_fragment_src = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform sampler2D u_Texture;

			in vec2 v_TexCoord;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";
		tex_shader_.reset(PH::Shader::Create(tex_vertex_src, tex_fragment_src));
	
		texture2d_ = PH::Texture2D::Create("assets/textures/test.jpg");
		tex_sdz_ = PH::Texture2D::Create("assets/textures/2.png");
	
		std::dynamic_pointer_cast<PH::OpenGLShader>(tex_shader_)->Bind();
		std::dynamic_pointer_cast<PH::OpenGLShader>(tex_shader_)->UploadUniforInt("u_Texture", 0);

	}

	void OnUpdate(PH::Timestep ts) override
	{
		// Camera
		if (PH::Input::IsKeyPressed(PH_KEY_LEFT))
			camera_pos_.x -= camera_move_speed_ * ts;
		else if (PH::Input::IsKeyPressed(PH_KEY_RIGHT))
			camera_pos_.x += camera_move_speed_ * ts;

		if (PH::Input::IsKeyPressed(PH_KEY_UP))
			camera_pos_.y += camera_move_speed_ * ts;
		else if (PH::Input::IsKeyPressed(PH_KEY_DOWN))
			camera_pos_.y -= camera_move_speed_ * ts;
		
		if (PH::Input::IsKeyPressed(PH_KEY_A))
			camera_rotation_ += camera_rota_speed_ * ts;
		else if (PH::Input::IsKeyPressed(PH_KEY_D))
			camera_rotation_ -= camera_rota_speed_ * ts;

		// Square
		if (PH::Input::IsKeyPressed(PH_KEY_J))
			square_pos_.x -= square_move_speed_ * ts;
		else if (PH::Input::IsKeyPressed(PH_KEY_L))
			square_pos_.x += square_move_speed_ * ts;

		if (PH::Input::IsKeyPressed(PH_KEY_I))
			square_pos_.y += square_move_speed_ * ts;
		else if (PH::Input::IsKeyPressed(PH_KEY_K))
			square_pos_.y -= square_move_speed_ * ts;

		PH::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		PH::RenderCommand::Clear();

		camera_.SetPosition(camera_pos_);
		camera_.SetRotation(camera_rotation_);

		PH::Renderer::BeginScene(camera_);
		{
			glm::vec4 blue = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
			glm::vec4 red = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			
			std::dynamic_pointer_cast<PH::OpenGLShader>(color_shader_)->Bind();
			std::dynamic_pointer_cast<PH::OpenGLShader>(color_shader_)->UploadUniforFloat4("u_Color", square_color_);

			for (int y = 0; y < 20; ++y) {
				for (int x = 0; x < 20; ++x) {
					glm::vec3 pos(x * 0.18f, y * 0.18f, 0.0f);
					glm::mat4 transform = glm::translate(glm::translate(glm::mat4(1.0f),square_pos_), pos) * scale;
					PH::Renderer::Submit(color_shader_, square_va_, transform);
				}
			}

			texture2d_->Bind();
			PH::Renderer::Submit(tex_shader_, square_va_, glm::mat4(1.0f));

			tex_sdz_->Bind();
			PH::Renderer::Submit(tex_shader_, square_va_,glm::translate(glm::mat4(1.0f),glm::vec3(0.2f,0.25f,0.0f))
				* glm::scale(glm::mat4(1.0f),glm::vec3(0.2f)));

			//PH::Renderer::Submit(shader_, vertex_array_);
		}
		PH::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));
		ImGui::End();
	}

	void OnEvent(PH::Event& event) override
	{

	}

private:
	// Render 
	PH::Ref<PH::Shader>shader_;
	PH::Ref<PH::VertexArray>vertex_array_;

	PH::Ref<PH::Shader>color_shader_, tex_shader_;
	PH::Ref<PH::VertexArray>square_va_;

	PH::Ref<PH::Texture2D>texture2d_;
	PH::Ref<PH::Texture2D>tex_sdz_;

	// Camera
	PH::OrthographicCamera camera_;
	float camera_rotation_;
	glm::vec3 camera_pos_;

	float camera_rota_speed_ = 60.0f;
	float camera_move_speed_ = 5.0f;

	// Square
	glm::vec3 square_pos_;
	float square_move_speed_ = 10.0f;
	glm::vec4 square_color_ = { 0.2f, 0.3f, 0.8f, 1.0f };
};

class Sandbox:public PH::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

// 实现入口方法
PH::Application* PH::CreateApplication()
{
	return new Sandbox();
}