#include "Sandbox2D.h"
#include "NagiEngine/Core/EntryPoint.h"

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
	// 创建纹理对象
	tex2d_props_.texture = Nagi::Texture2D::Create("assets/textures/test.jpg");

	tex2d_test2_props_.texture = Nagi::Texture2D::Create("assets/textures/2.png");

	backboard_tex_.texture= Nagi::Texture2D::Create("assets/textures/Checkerboard.png");
	backboard_tex_.tiling_factor = 25;
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Nagi::Timestep ts)
{
	camera_controller_.OnUpdate(ts);
	fps_ = 1.0f / ts;
	quad_tex2_props_.rotation += ts*50;
	
	// Render
	Nagi::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
	Nagi::RenderCommand::Clear();

	Nagi::Renderer2D::ResetStatistics();
	{
		PROFILE_SCOPE("Renderer");

		Nagi::Renderer2D::BeginScene(camera_controller_.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f) {
			for (float x = -5.0f; x < 5.0f; x += 0.5f) {
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Nagi::Renderer2D::DrawQuad({ { x * 100, y * 100 }, { 4.5f, 4.5f } }, color);
			}
		}
		Nagi::Renderer2D::EndScene();

		Nagi::Renderer2D::BeginScene(camera_controller_.GetCamera());
		{	
			Nagi::Renderer2D::DrawQuad(backboard_props_, backboard_tex_);
			Nagi::Renderer2D::DrawQuad(quad_tex_props_, tex2d_props_);
			Nagi::Renderer2D::DrawQuad(quad_props_, square_color_);
			Nagi::Renderer2D::DrawQuad(quad_tex2_props_, tex2d_test2_props_);
		}
		Nagi::Renderer2D::EndScene();

	}
}

void Sandbox2D::DrawGui()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));
	ImGui::DragFloat3("Position", glm::value_ptr(quad_props_.position));
	ImGui::DragFloat2("Size", glm::value_ptr(quad_props_.size));
	ImGui::DragFloat("Rotation", &quad_props_.rotation);
	ImGui::DragFloat("Texture Tiling Factor", &tex2d_props_.tiling_factor);
	ImGui::DragFloat3("Tex Position", glm::value_ptr(quad_tex_props_.position));
	ImGui::DragFloat2("Tex Size", glm::value_ptr(quad_tex_props_.size));
	ImGui::DragFloat3("Tex2 Position", glm::value_ptr(quad_tex2_props_.position));
	ImGui::DragFloat2("Tex2 Size", glm::value_ptr(quad_tex2_props_.size));
	for (auto& result : profile_results_) {
		char label[50];
		strcpy_s(label, "%.3fms ");
		strcat_s(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	profile_results_.clear();

	{
		char fps[20];
		strcpy_s(fps, "FPS: ");
		strcat_s(fps, "%.3f");
		ImGui::Text(fps, fps_);
	}

	auto stats = Nagi::Renderer2D::GetStatistics();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.batch_count);
	ImGui::Text("Quads: %d", stats.quad_count);
	ImGui::Text("Triangles: %d", stats.GetTriangleCount());

	uint32_t backboard_id = backboard_tex_.texture->GetId();
	ImGui::Image((void*)backboard_id, ImVec2{ 256.0f, 256.0f });
	ImGui::End();
}

void Sandbox2D::OnImGuiRender()
{
	// Note: Switch this to true to enable dockspace
	static bool dockingEnabled = false;
	if (dockingEnabled) {
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Nagi::Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		DrawGui();

		ImGui::End();
	}
	else {
		DrawGui();
	}
}

void Sandbox2D::OnEvent(Nagi::Event& event)
{
	camera_controller_.OnEvent(event);
}