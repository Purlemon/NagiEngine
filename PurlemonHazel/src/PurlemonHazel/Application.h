#pragma once
#include "Core.h"
#include "Event/Event.h"
#include "Window.h"
#include "ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

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
		ImGuiLayer* imgui_layer_;
		bool running_ = true;
		LayerStack layer_stack_;

		// Render 
		unsigned int vertex_array_;
		std::unique_ptr<Shader>shader_;
		std::unique_ptr<VertexBuffer>vertex_buffer_;
		std::unique_ptr<IndexBuffer>index_buffer_;
	private:
		static Application* instance_;
	};

	// 将在客户端被定义
	Application* CreateApplication();
}


