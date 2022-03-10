#pragma once

#include "PurlemonHazel/Renderer/OrthographicCamera.h"
#include "PurlemonHazel/Core/Timestep.h"

#include "PurlemonHazel/Event/ApplicationEvent.h"
#include "PurlemonHazel/Event/MouseEvent.h"

namespace PH {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspect_ratio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline OrthographicCamera& GetCamera() { return camera_; }
		inline const OrthographicCamera& GetCamera() const { return camera_; }
	
		float GetZoomLevel() const { return zoom_level_; }
		void SetZoomLevel(float level) { zoom_level_ = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float aspect_ratio_;
		float zoom_level_ = 1.0f;
		OrthographicCamera camera_;

		bool rotation_;
		glm::vec3 camera_pos_ = { 0.0f,0.0f,0.0f };
		float camera_rotation_;
		float camera_rota_speed_ = 60.0f;
		float camera_move_speed_;
	};

}
