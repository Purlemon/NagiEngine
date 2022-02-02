#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"

#include "GLFW/glfw3.h"

namespace PurlemonHazel {

	Application::Application()
	{
		window_ = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (running_) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window_->OnUpdate();
		}
	}
}