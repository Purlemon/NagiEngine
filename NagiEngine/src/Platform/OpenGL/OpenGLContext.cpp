#include "OpenGLContext.h"
#include "NagiEngine/Core/Log.h"

namespace Nagi {

	OpenGLContext::OpenGLContext(struct GLFWwindow* window_handle)
		:window_handle_(window_handle)
	{
		NAGI_CORE_ASSERT(window_handle_, "Window handle is null! ");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(window_handle_);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NAGI_CORE_ASSERT(status, "Failed to initialize Glad!");

		NAGI_CORE_INFO("OpenGL Info:");
		NAGI_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		NAGI_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		NAGI_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(window_handle_);
	}

}