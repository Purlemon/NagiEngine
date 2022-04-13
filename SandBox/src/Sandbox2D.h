#pragma once

#include "NagiEngine.h"

class Sandbox2D :public Nagi::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Nagi::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(Nagi::Event& event) override;
private:

	Nagi::Ref<Nagi::Shader> shader_;
	Nagi::Ref<Nagi::VertexArray>square_va_;
	Nagi::Texture2DPorps tex2d_props_;
	Nagi::Texture2DPorps tex2d_test2_props_;

	Nagi::OrthographicCameraController camera_controller_;

	glm::vec4 square_color_ = { 0.2f, 0.3f, 0.8f, 1.0f };
	Nagi::QuadProps quad_props_ = { glm::vec2(-2.0f), {10.0f, 10.0f} };
	Nagi::QuadProps quad_tex_props_ = { glm::vec2(2.0f), {20.0f, 20.0f} };
	Nagi::QuadProps quad_tex2_props_ = { glm::vec2(1.0f), {10.0f, 10.0f} };

	// –‘ƒ‹≈‰÷√
	struct ProfileResult
	{
		const char* Name;
		float Time;
	};
	std::vector<ProfileResult> profile_results_;
	float fps_ = 0.0f;
};