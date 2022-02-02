#pragma once
#include "Core.h"
#include "Event/Event.h"
#include "Window.h"

namespace PurlemonHazel {

	class PH_API Application
	{
	public:
		Application();
		virtual ~Application(); // ����������������ͬʱ��������

		void Run();
	private:
		std::unique_ptr<Window>window_;
		bool running_ = true;
	};

	// ���ڿͻ��˱�����
	Application* CreateApplication();
}


