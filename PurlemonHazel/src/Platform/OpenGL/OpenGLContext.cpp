#include "OpenGLContext.h"
#include "PurlemonHazel/Core/Log.h"

namespace PH {

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

		PH_CORE_INFO("OpenGL Info:");
		PH_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		PH_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		PH_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(window_handle_);
	}

}