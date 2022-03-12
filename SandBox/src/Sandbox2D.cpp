#include "Sandbox2D.h"
#include "PurlemonHazel/Core/EntryPoint.h"

#include "imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}
private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer(name, [&](ProfileResult pro_res) {profile_results_.push_back(pro_res); })

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

	{
		PROFILE_SCOPE("Renderer");
		PH::Renderer2D::BeginScene(camera_controller_.GetCamera());
		{
			PH::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f,1.0f }, square_color_);
			PH::Renderer2D::DrawQuad({ (glm::vec3)square_pos_ / 100.0f }, { 1.0f,1.0f }, texture2d_);
		}
		PH::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));
	ImGui::DragInt3("Pos", glm::value_ptr(square_pos_));
	for (auto& result : profile_results_) {
		char label[50];
		strcpy_s(label, "%.3fms ");
		strcat_s(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	profile_results_.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(PH::Event& event)
{
	camera_controller_.OnEvent(event);
}