#include "ngpch.h"

#include "OrthographicCamera.h"

namespace Nagi {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:projection_matrix_(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), 
		view_matrix_(1.0f), position_(glm::vec3(0.0f,0.0f,0.0f))
	{
		projection_view_matrix_ = projection_matrix_ * view_matrix_;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		projection_matrix_ = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		projection_view_matrix_ = projection_matrix_ * view_matrix_;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position_)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0.0f, 0.0f, 1.0f));
		view_matrix_ = glm::inverse(transform);
		projection_view_matrix_ = projection_matrix_ * view_matrix_;
	}
}