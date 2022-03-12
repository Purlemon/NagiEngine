#pragma once

#include "PurlemonHazel/Renderer/GraphicsContext.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace PH {

	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(struct GLFWwindow* window_handle);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* window_handle_;
	};

}