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
	texture2d_ = PH::Texture2D::Create("assets/textures/test.jpg");
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

	PH::Renderer2D::BeginScene(camera_controller_.GetCamera());
	{
		PH::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f,1.0f }, square_color_);
		PH::Renderer2D::DrawQuad({ (glm::vec3)square_pos_ / 100.0f }, { 1.0f,1.0f }, texture2d_);
	}
	PH::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));
	ImGui::DragInt3("Pos", glm::value_ptr(square_pos_));
	ImGui::End();
}

void Sandbox2D::OnEvent(PH::Event& event)
{
	camera_controller_.OnEvent(event);
}