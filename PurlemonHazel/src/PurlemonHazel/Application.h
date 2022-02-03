#pragma once
#include "Core.h"
#include "Event/Event.h"
#include "Window.h"

namespace PurlemonHazel {

	class PH_API Application
	{
	public:
		Application();
		virtual ~Application(); // 虚析构函数，调用同时调用子类

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(class WindowCloseEvent& e);

		std::unique_ptr<Window>window_;
		bool running_ = true;
	};

	// 将在客户端被定义
	Application* CreateApplication();
}


