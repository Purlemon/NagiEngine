#pragma once
#include "Core.h"
#include "Event/Event.h"

namespace PurlemonHazel {

	class PH_API Application
	{
	public:
		Application();
		virtual ~Application(); // 虚析构函数，调用同时调用子类

		void Run();
	};

	// 将在客户端被定义
	Application* CreateApplication();
}


