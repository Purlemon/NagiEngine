#pragma once
#include "Core.h"
#include "NagiEngine/Event/Event.h"
#include "Window.h"
#include "NagiEngine/ImGui/ImGuiLayer.h"
#include "LayerStack.h"

#include "Timestep.h"

#include "NagiEngine/Renderer/VertexArray.h"
#include "NagiEngine/Renderer/Shader.h"
#include "NagiEngine/Renderer/Buffer.h"
#include "NagiEngine/Renderer/OrthographicCamera.h"

namespace Nagi {

	class NAGI_API Application
	{
	public:
		Application(const std::string& name = "Nagi App", ng_uint32 width = 1280, ng_uint32 height = 720);
		virtual ~Application(); // 虚析构函数，调用同时调用子类

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void OnEvent(Event& e);

		void Close();

		static Application& Get() { return *instance_; }
		Window& GetWindow() { return *window_; }

		ImGuiLayer* GetImGuiLayer() { return imgui_layer_; }

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


