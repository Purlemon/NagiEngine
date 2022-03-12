#pragma once
#include "Core.h"
#include "PurlemonHazel/Event/Event.h"
#include "Window.h"
#include "PurlemonHazel/ImGui/ImGuiLayer.h"
#include "LayerStack.h"

#include "Timestep.h"

#include "PurlemonHazel/Renderer/VertexArray.h"
#include "PurlemonHazel/Renderer/Shader.h"
#include "PurlemonHazel/Renderer/Buffer.h"
#include "PurlemonHazel/Renderer/OrthographicCamera.h"

namespace PH {

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
		bool OnWindowResize(class WindowResizeEvent& e);
	private:
		std::unique_ptr<Window>window_;
		ImGuiLayer* imgui_layer_;
		bool running_ = true;
		bool minimized_ = false; 
		LayerStack layer_stack_;

		Timestep timestep_;
		float last_frame_time_ = 0.0f;
	private:
		static Application* instance_;
	};

	// 将在客户端被定义
	Application* CreateApplication();
}


