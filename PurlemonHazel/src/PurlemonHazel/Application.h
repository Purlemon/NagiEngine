#pragma once
#include "Core.h"
#include "Event/Event.h"
#include "Window.h"
#include "ImGui/ImGuiLayer.h"
#include "LayerStack.h"

#include "Core/Timestep.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/OrthographicCamera.h"

namespace PurlemonHazel {

	class PH_API Application
	{
	public:
		Application();
		virtual ~Application(); // ����������������ͬʱ��������

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void OnEvent(Event& e);

		inline static Application& Get() { return *instance_; }
		inline Window& GetWindow() { return *window_; }
	private:
		bool OnWindowClose(class WindowCloseEvent& e);
	private:
		std::unique_ptr<Window>window_;
		ImGuiLayer* imgui_layer_;
		bool running_ = true;
		LayerStack layer_stack_;

		Timestep timestep_;
		float last_frame_time_ = 0.0f;
	private:
		static Application* instance_;
	};

	// ���ڿͻ��˱�����
	Application* CreateApplication();
}


