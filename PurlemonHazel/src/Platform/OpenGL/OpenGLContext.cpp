#include "OpenGLContext.h"

namespace PurlemonHazel {

	OpenGLContext::OpenGLContext(class GLFWwindow* window_handle)
		:window_handle_(window_handle)
	{
		PH_CORE_ASSERT(window_handle_, "Window handle is null! ");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(window_handle_);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PH_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(window_handle_);
	}

}