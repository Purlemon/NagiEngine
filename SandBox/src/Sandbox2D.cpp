#include "Sandbox2D.h"
#include "PurlemonHazel/Core/EntryPoint.h"

#include "imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), camera_controller_(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	square_va_ = PH::VertexArray::Create();

	float square_vertices[4 * 3] = {
		-0.75f, -0.75f, 0.0f, 
		 0.75f, -0.75f, 0.0f,
		 0.75f,  0.75f, 0.0f,
		-0.75f,  0.75f, 0.0f
	};

	PH::Ref<PH::VertexBuffer>square_vb;
	square_vb.reset(PH::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
	square_vb->SetLayout({
		{ PH::ShaderDataType::Float3, "a_Position" },
	});
	square_va_->AddVertexBuffer(square_vb);

	unsigned int square_indices[6] = { 0,1,2,2,3,0 };
	PH::Ref<PH::IndexBuffer>square_ib;
	square_ib.reset(PH::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(unsigned int)));
	square_va_->SetIndexBuffer(square_ib);

	shader_ =PH::Shader::Create("flat_color", "assets/shaders/vertex/flat_color.vert", "assets/shaders/fragment/flat_color.frag");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(PH::Timestep ts)
{
	camera_controller_.OnUpdate(ts);
	// Render
	PH::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
	PH::RenderCommand::Clear();

	PH::Renderer::BeginScene(camera_controller_.GetCamera());
	{
		std::dynamic_pointer_cast<PH::OpenGLShader>(shader_)->Bind();
		std::dynamic_pointer_cast<PH::OpenGLShader>(shader_)->UploadUniforFloat4("u_Color", square_color_);

		PH::Renderer::Submit(shader_, square_va_, glm::mat4(1.0f));
	}
	PH::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));
	ImGui::End();
}

void Sandbox2D::OnEvent(PH::Event& event)
{
	camera_controller_.OnEvent(event);
}