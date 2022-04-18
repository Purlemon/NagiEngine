#include "ngpch.h"

#include "OrthographicCameraController.h"

#include "NagiEngine/NagiCode/KeyCodes.h"
#include "NagiEngine/Core/Input.h"

namespace Nagi {

	OrthographicCameraController::OrthographicCameraController(float aspect_ratio, bool rotation)
		:camera_(-aspect_ratio_ * zoom_level_, aspect_ratio_* zoom_level_, -zoom_level_, zoom_level_),
		aspect_ratio_(aspect_ratio), rotation_(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(NAGI_KEY_A))
			camera_pos_.x -= camera_move_speed_ * ts;
		else if (Input::IsKeyPressed(NAGI_KEY_D))
			camera_pos_.x += camera_move_speed_ * ts;

		if (Input::IsKeyPressed(NAGI_KEY_W))
			camera_pos_.y += camera_move_speed_ * ts;
		else if (Input::IsKeyPressed(NAGI_KEY_S))
			camera_pos_.y -= camera_move_speed_ * ts;

		if (Input::IsKeyPressed(NAGI_KEY_SPACE)) {
			camera_pos_ = glm::vec3(0.0f, 0.0f, 0.0f);
			zoom_level_ = 1.0f;
			camera_.SetProjection(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);
			camera_rotation_ = 0.0f;
		}

		if (rotation_) {
			if (Input::IsKeyPressed(NAGI_KEY_Q))
				camera_rotation_ += camera_rota_speed_ * ts;
			else if (Input::IsKeyPressed(NAGI_KEY_E))
				camera_rotation_ -= camera_rota_speed_ * ts;

			camera_.SetRotation(camera_rotation_);
		}

		camera_.SetPosition(camera_pos_);

		camera_move_speed_ = zoom_level_ * 2.0f; // Ëõ·Å´óÒÆ¶¯Âý
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(NAGI_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(NAGI_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		aspect_ratio_ = width / height;
		camera_.SetProjection(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		zoom_level_ -= e.GetYOffset() * 0.5f;
		zoom_level_ = std::max(zoom_level_, 0.25f);
		camera_.SetProjection(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}
