#pragma once

#include "PurlemonHazel.h"

class Sandbox2D :public PH::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(PH::Timestep ts) override;
	void OnImGuiRender() override;
	void OnEvent(PH::Event& event) override;
private:

	PH::Ref<PH::Shader> shader_;
	PH::Ref<PH::VertexArray>square_va_;
	PH::Texture2DPorps tex2d_props_;

	PH::OrthographicCameraController camera_controller_;

	glm::vec4 square_color_ = { 0.2f, 0.3f, 0.8f, 1.0f };
	PH::QuadProps quad_props_ = { glm::vec2(0.0f), {10.0f, 10.0f} };

	// –‘ƒ‹≈‰÷√
	struct ProfileResult
	{
		const char* Name;
		float Time;
	};
	std::vector<ProfileResult> profile_results_;
};