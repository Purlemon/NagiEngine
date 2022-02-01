#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"

namespace PurlemonHazel {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 1080);
		PH_TRACE(e);
		if (e.IsInCategory(kEventCategoryApplication))
			PH_INFO(e.ToString() + " kEventCategoryApplication");
		if (e.IsInCategory(kEventCategoryInput))
			PH_WARN(e.ToString() + " kEventCategoryInput");
		if (e.IsInCategory(kEventCategoryKeyboard))
			PH_ERROR(e.ToString() + " kEventCategoryKeyboard");
		while (true) {

		}
	}
}