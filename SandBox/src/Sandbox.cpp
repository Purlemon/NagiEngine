#include<NagiEngine.h>

#include "imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Nagi::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), camera_controller_(1280.0f / 720.0f, true), square_pos_(0.0f)
	{

		// ----------------------------
		// OpenGL Render
		// ----------------------------

		// 三角形
		vertex_array_ = Nagi::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		Nagi::BufferLayout layout = {
			{Nagi::ShaderDataType::Float3, "a_Position"},
			{Nagi::ShaderDataType::Float4, "a_Color"},
		};
		Nagi::Ref<Nagi::VertexBuffer>vertex_buffer_;
		vertex_buffer_ = Nagi::VertexBuffer::Create(vertices, sizeof(vertices));
		vertex_buffer_->SetLayout(layout);
		vertex_array_->AddVertexBuffer(vertex_buffer_);

		ph_uint32 indices[3] = { 0,1,2 };
		Nagi::Ref<Nagi::IndexBuffer>index_buffer_;
		index_buffer_ = Nagi::IndexBuffer::Create(indices, sizeof(indices) / sizeof(ph_uint32));
		vertex_array_->SetIndexBuffer(index_buffer_);

		// 正方形
		square_va_ = Nagi::VertexArray::Create();

		float square_vertices[5 * 4] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.0f, 1.0f,
		};

		Nagi::Ref<Nagi::VertexBuffer>square_vb;
		square_vb = Nagi::VertexBuffer::Create(square_vertices, sizeof(square_vertices));
		square_vb->SetLayout({
			{ Nagi::ShaderDataType::Float3, "a_Position" },
			{ Nagi::ShaderDataType::Float2, "a_Position" }
			});
		square_va_->AddVertexBuffer(square_vb);

		ph_uint32 square_indices[6] = { 0,1,2,2,3,0 };
		Nagi::Ref<Nagi::IndexBuffer>square_ib;
		square_ib = Nagi::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(ph_uint32));
		square_va_->SetIndexBuffer(square_ib);

		auto tex_shader_ = shader_lib_.Load("color", "assets/shaders/vertex/color.vert", "assets/shaders/fragment/color.frag");
		shader_lib_.Load("texture", "assets/shaders/vertex/texture.vert", "assets/shaders/fragment/texture.frag");
	
		texture2d_ = Nagi::Texture2D::Create("assets/textures/test.jpg");
		tex_sdz_ = Nagi::Texture2D::Create("assets/textures/2.png");
	
		std::dynamic_pointer_cast<Nagi::OpenGLShader>(tex_shader_)->Bind();
		std::dynamic_pointer_cast<Nagi::OpenGLShader>(tex_shader_)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Nagi::Timestep ts) override
	{
		// Square
		if (Nagi::Input::IsKeyPressed(NAGI_KEY_J))
			square_pos_.x -= square_move_speed_ * ts;
		else if (Nagi::Input::IsKeyPressed(NAGI_KEY_L))
			square_pos_.x += square_move_speed_ * ts;

		if (Nagi::Input::IsKeyPressed(NAGI_KEY_I))
			square_pos_.y += square_move_speed_ * ts;
		else if (Nagi::Input::IsKeyPressed(NAGI_KEY_K))
			square_pos_.y -= square_move_speed_ * ts;

		// Update
		camera_controller_.OnUpdate(ts);

		// Render
		Nagi::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		Nagi::RenderCommand::Clear();

		Nagi::Renderer::BeginScene(camera_controller_.GetCamera());
		{
			glm::vec4 blue = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
			glm::vec4 red = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			
			auto color = shader_lib_.Get("color");
			std::dynamic_pointer_cast<Nagi::OpenGLShader>(color)->Bind();
			std::dynamic_pointer_cast<Nagi::OpenGLShader>(color)->UploadUniformFloat4("u_Color", square_color_);

			for (int y = 0; y < 20; ++y) {
				for (int x = 0; x < 20; ++x) {
					glm::vec3 pos(x * 0.18f, y * 0.18f, 0.0f);
					glm::mat4 transform = glm::translate(glm::translate(glm::mat4(1.0f),square_pos_), pos) * scale;
					Nagi::Renderer::Submit(color, square_va_, transform);
				}
			}

			auto texture = shader_lib_.Get("texture");
			texture2d_->Bind();
			Nagi::Renderer::Submit(texture, square_va_, glm::mat4(1.0f));

			tex_sdz_->Bind();
			Nagi::Renderer::Submit(texture, square_va_,glm::translate(glm::mat4(1.0f),glm::vec3(0.2f,0.25f,0.0f))
				* glm::scale(glm::mat4(1.0f),glm::vec3(0.2f)));

			//Nagi::Renderer::Submit(shader_, vertex_array_);
		}
		Nagi::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));
		ImGui::End();
	}

	void OnEvent(Nagi::Event& event) override
	{
		camera_controller_.OnEvent(event);
	}

private:
	// Render 
	Nagi::ShaderLibrary shader_lib_;
	Nagi::Ref<Nagi::VertexArray>vertex_array_;

	Nagi::Ref<Nagi::VertexArray>square_va_;

	Nagi::Ref<Nagi::Texture2D>texture2d_;
	Nagi::Ref<Nagi::Texture2D>tex_sdz_;

	// Camera
	Nagi::OrthographicCameraController camera_controller_;

	// Square
	glm::vec3 square_pos_;
	float square_move_speed_ = 10.0f;
	glm::vec4 square_color_ = { 0.2f, 0.3f, 0.8f, 1.0f };
};

class Sandbox:public Nagi::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}
};

// 实现入口方法
Nagi::Application* Nagi::CreateApplication()
{
	return new Sandbox();
}