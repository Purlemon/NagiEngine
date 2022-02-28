#include<PurlemonHazel.h>

#include "imgui.h"

#define PH PurlemonHazel

class ExampleLayer : public PurlemonHazel::Layer
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
		std::shared_ptr<PH::VertexBuffer>vertex_buffer_;
		vertex_buffer_.reset(PH::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertex_buffer_->SetLayout(layout);
		vertex_array_->AddVertexBuffer(vertex_buffer_);

		unsigned int indices[3] = { 0,1,2 };
		std::shared_ptr<PH::IndexBuffer>index_buffer_;
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

		shader_.reset(new PH::Shader(vertex_src, fragment_src));

		// 正方形
		square_va_.reset(PH::VertexArray::Create());

		float square_vertices[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<PH::VertexBuffer>square_vb;
		square_vb.reset(PH::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
		square_vb->SetLayout({
			{ PH::ShaderDataType::Float3, "a_Position" }
			});
		square_va_->AddVertexBuffer(square_vb);

		unsigned int square_indices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<PH::IndexBuffer>square_ib;
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

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
			}
		)";
		blue_shader_.reset(new PH::Shader(blue_vertex_src, blue_fragment_src));
	}

	virtual void OnImGuiRender() override
	{

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

		PurlemonHazel::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		PurlemonHazel::RenderCommand::Clear();

		camera_.SetPosition(camera_pos_);
		camera_.SetRotation(camera_rotation_);

		PurlemonHazel::Renderer::BeginScene(camera_);
		{
			PurlemonHazel::Renderer::Submit(blue_shader_, square_va_, glm::translate(glm::mat4(1.0f),square_pos_));

			PurlemonHazel::Renderer::Submit(shader_, vertex_array_);
		}
		PurlemonHazel::Renderer::EndScene();
	}

	void OnEvent(PurlemonHazel::Event& event) override
	{

	}

private:
	// Render 
	std::shared_ptr<PurlemonHazel::Shader>shader_;
	std::shared_ptr<PurlemonHazel::VertexArray>vertex_array_;

	std::shared_ptr<PurlemonHazel::Shader>blue_shader_;
	std::shared_ptr<PurlemonHazel::VertexArray>square_va_;

	// Camera
	PurlemonHazel::OrthographicCamera camera_;
	float camera_rotation_;
	glm::vec3 camera_pos_;

	float camera_rota_speed_ = 60.0f;
	float camera_move_speed_ = 5.0f;

	// Square
	glm::vec3 square_pos_;
	float square_move_speed_ = 10.0f;
};

class Sandbox:public PurlemonHazel::Application
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
PurlemonHazel::Application* PurlemonHazel::CreateApplication()
{
	return new Sandbox();
}