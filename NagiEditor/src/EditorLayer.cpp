#include "EditorLayer.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

namespace Nagi {

	EditorLayer::EditorLayer()
		:Layer("EditorLayer"), camera_controller_(1280.0f / 720.0f, true)
	{
	}

	void EditorLayer::OnAttach()
	{
		// 创建纹理对象
		tex2d_props_.texture = Texture2D::Create("assets/textures/test.jpg");

		tex2d_test2_props_.texture = Texture2D::Create("assets/textures/2.png");

		backboard_tex_.texture = Texture2D::Create("assets/textures/Checkerboard.png");
		backboard_tex_.tiling_factor = 25;

		// 绑定帧缓冲
		frame_buffer_ = Framebuffer::Create({ 1280,720 });
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		camera_controller_.OnUpdate(ts);
		fps_ = 1.0f / ts;
		quad_tex2_props_.rotation += ts * 50;

		frame_buffer_->Bind();

		// Render
		RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderCommand::Clear();

		Renderer2D::ResetStatistics();
		{
	
			Renderer2D::BeginScene(camera_controller_.GetCamera());

			for (float y = -5.0f; y < 5.0f; y += 0.5f) {
				for (float x = -5.0f; x < 5.0f; x += 0.5f) {
					glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
					Renderer2D::DrawQuad({ { x * 100, y * 100 }, { 4.5f, 4.5f } }, color);
				}
			}
			Renderer2D::EndScene();

			Renderer2D::BeginScene(camera_controller_.GetCamera());
			{
				Renderer2D::DrawQuad(backboard_props_, backboard_tex_);
				Renderer2D::DrawQuad(quad_tex_props_, tex2d_props_);
				Renderer2D::DrawQuad(quad_props_, square_color_);
				Renderer2D::DrawQuad(quad_tex2_props_, tex2d_test2_props_);
			}
			Renderer2D::EndScene();

			frame_buffer_->Unbind();
		}
	}

	void EditorLayer::DrawGui()
	{
		// ------------------------------------------
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

		auto stats = Renderer2D::GetStatistics();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.batch_count);
		ImGui::Text("Quads: %d", stats.quad_count);
		ImGui::Text("Triangles: %d", stats.GetTriangleCount());

		{
			char fps[20];
			strcpy_s(fps, "FPS: ");
			strcat_s(fps, "%.3f");
			ImGui::Text(fps, fps_);
		}
		ImGui::End();

		// --------------------------------------------------
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });// 设置图片充满窗口
		ImGui::Begin("Viewport");

		ImVec2 vp_size = ImGui::GetContentRegionAvail();
		glm::vec2 viewport_size = { vp_size.x,vp_size.y };
		if (last_viewport_size_ != viewport_size) {
			frame_buffer_->ResizeColorAttachment(viewport_size.x, viewport_size.y);
			last_viewport_size_ = viewport_size;

			camera_controller_.OnResize(vp_size.x, vp_size.y);
		}

		ImGui::Image((void*)frame_buffer_->GetColorAttachmentRendererID(), vp_size, { 0,1 }, { 1,0 });
		
		ImGui::End();
		ImGui::PopStyleVar();
	}

	void EditorLayer::OnImGuiRender()
	{
		// Note: Switch this to true to enable dockspace
		static bool dockingEnabled = true;
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

					if (ImGui::MenuItem("Exit")) Application::Get().Close();
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

	void EditorLayer::OnEvent(Event& event)
	{
		camera_controller_.OnEvent(event);
	}

}

