#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "NagiEngine/Core/Log.h"

namespace Nagi {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition()const { return position_; }
		void SetPosition(const glm::vec3& position) { position_ = position; RecalculateViewMatrix();}

		float GetRotation() { return rotation_; }
		void SetRotation(float rotation) { rotation_ = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return projection_matrix_; }
		const glm::mat4& GetViewMatrix() const { return view_matrix_; }
		const glm::mat4& GetProjectionViewMatrix() const { return projection_view_matrix_; }
	
	private:
		void RecalculateViewMatrix(); 
	private:
		glm::mat4 projection_matrix_;
		glm::mat4 view_matrix_;
		glm::mat4 projection_view_matrix_;

		glm::vec3 position_;
		float rotation_ = 0.0f;
	};

}