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
		virtual ~Application(); // ÐéÎö¹¹º¯Êý£¬µ÷ÓÃÍ¬Ê±µ÷ÓÃ×ÓÀà

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

<<<<<<< HEAD:PurlemonHazel/src/PurlemonHazel/Core/Application.h
		Timestep timestep_;
		float last_frame_time_ = 0.0f;
=======
		// Render 
		std::shared_ptr<Shader>shader_;
		std::shared_ptr<VertexArray>vertex_array_;

		std::shared_ptr<Shader>blue_shader_;
		std::shared_ptr<VertexArray>square_va_;

		OrthographicCamera camera_;
>>>>>>> parent of 8f1285a (å°†æ¸²æŸ“ç§»åŠ¨åˆ°sandboxä¸­):PurlemonHazel/src/PurlemonHazel/Application.h
	private:
		static Application* instance_;
	};

	// ½«ÔÚ¿Í»§¶Ë±»¶¨Òå
	Application* CreateApplication();
}


