#include<PurlemonHazel.h>

#include "imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public PH::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), camera_controller_(1280.0f / 720.0f, true), square_pos_(0.0f)
	{

		// ----------------------------
		// OpenGL Render
		// ----------------------------

		// 三角形
		vertex_array_ = PH::VertexArray::Create();

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

		// 正方形
		square_va_ = PH::VertexArray::Create();

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

		auto tex_shader_ = shader_lib_.Load("color", "assets/shaders/vertex/color.vert", "assets/shaders/fragment/color.frag");
		shader_lib_.Load("texture", "assets/shaders/vertex/texture.vert", "assets/shaders/fragment/texture.frag");
	
		texture2d_ = PH::Texture2D::Create("assets/textures/test.jpg");
		tex_sdz_ = PH::Texture2D::Create("assets/textures/2.png");
	
		std::dynamic_pointer_cast<PH::OpenGLShader>(tex_shader_)->Bind();
		std::dynamic_pointer_cast<PH::OpenGLShader>(tex_shader_)->UploadUniforInt("u_Texture", 0);

	}

	void OnUpdate(PH::Timestep ts) override
	{
		// Square
		if (PH::Input::IsKeyPressed(PH_KEY_J))
			square_pos_.x -= square_move_speed_ * ts;
		else if (PH::Input::IsKeyPressed(PH_KEY_L))
			square_pos_.x += square_move_speed_ * ts;

		if (PH::Input::IsKeyPressed(PH_KEY_I))
			square_pos_.y += square_move_speed_ * ts;
		else if (PH::Input::IsKeyPressed(PH_KEY_K))
			square_pos_.y -= square_move_speed_ * ts;

		// Update
		camera_controller_.OnUpdate(ts);

		// Render
		PH::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		PH::RenderCommand::Clear();

		PH::Renderer::BeginScene(camera_controller_.GetCamera());
		{
			glm::vec4 blue = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
			glm::vec4 red = glm::vec4(0.8f, 0.2f, 0.3f, 1.0f);

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			
			auto color = shader_lib_.Get("color");
			std::dynamic_pointer_cast<PH::OpenGLShader>(color)->Bind();
			std::dynamic_pointer_cast<PH::OpenGLShader>(color)->UploadUniforFloat4("u_Color", square_color_);

			for (int y = 0; y < 20; ++y) {
				for (int x = 0; x < 20; ++x) {
					glm::vec3 pos(x * 0.18f, y * 0.18f, 0.0f);
					glm::mat4 transform = glm::translate(glm::translate(glm::mat4(1.0f),square_pos_), pos) * scale;
					PH::Renderer::Submit(color, square_va_, transform);
				}
			}

			auto texture = shader_lib_.Get("texture");
			texture2d_->Bind();
			PH::Renderer::Submit(texture, square_va_, glm::mat4(1.0f));

			tex_sdz_->Bind();
			PH::Renderer::Submit(texture, square_va_,glm::translate(glm::mat4(1.0f),glm::vec3(0.2f,0.25f,0.0f))
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
		camera_controller_.OnEvent(event);
	}

private:
	// Render 
	PH::ShaderLibrary shader_lib_;
	PH::Ref<PH::VertexArray>vertex_array_;

	PH::Ref<PH::VertexArray>square_va_;

	PH::Ref<PH::Texture2D>texture2d_;
	PH::Ref<PH::Texture2D>tex_sdz_;

	// Camera
	PH::OrthographicCameraController camera_controller_;

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
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
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