#pragma once

#include "NagiEngine.h"

#include "imgui.h"

namespace Nagi {

	class EditorLayer :public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;

		void DrawGui();
	private:

		Ref<Shader> shader_;
		Ref<VertexArray>square_va_;
		Ref<Framebuffer>frame_buffer_;
		Texture2DPorps backboard_tex_;
		Texture2DPorps tex2d_props_;
		Texture2DPorps tex2d_test2_props_;

		OrthographicCameraController camera_controller_;

		glm::vec4 square_color_ = { 0.2f, 0.3f, 0.8f, 1.0f };
		QuadProps backboard_props_ = { glm::vec3(0.0f,0.0f,-1.0f), {250.0f, 250.0f} };
		QuadProps quad_props_ = { glm::vec3(-50.0f,-50.0f,2.0f), {10.0f, 10.0f} };
		QuadProps quad_tex_props_ = { glm::vec3(50.0f,50.0f,1.0f), {20.0f, 20.0f} };
		QuadProps quad_tex2_props_ = { glm::vec3(10.0f,10.0f,3.0f), {10.0f, 10.0f} };

		// GUI
		bool viewport_focused_ = false, viewport_hovered_ = false;
		glm::vec2 last_viewport_size_ = { 0.0f,0.0f };

		// –‘ƒ‹≈‰÷√
		float fps_ = 0.0f;
	};

}
