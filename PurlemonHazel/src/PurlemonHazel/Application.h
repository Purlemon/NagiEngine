#pragma once
#include "Core.h"
#include "Event/Event.h"
#include "Window.h"
#include "LayerStack.h"

namespace PurlemonHazel {

	class PH_API Application
	{
	public:
		Application();
		virtual ~Application(); // 虚析构函数，调用同时调用子类

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void OnEvent(Event& e);

		inline static Application& Get() { return *instance_; }
		inline Window& GetWindow() { return *window_; }
	private:
		bool OnWindowClose(class WindowCloseEvent& e);

		std::unique_ptr<Window>window_;
		bool running_ = true;
		LayerStack layer_stack_;
	private:
		static Application* instance_;
	};

	// 将在客户端被定义
	Application* CreateApplication();
}


