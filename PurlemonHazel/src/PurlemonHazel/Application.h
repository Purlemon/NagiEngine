#pragma once
#include "Core.h"
#include "Event/Event.h"

namespace PurlemonHazel {

	class PH_API Application
	{
	public:
		Application();
		virtual ~Application(); // ����������������ͬʱ��������

		void Run();
	};

	// ���ڿͻ��˱�����
	Application* CreateApplication();
}


