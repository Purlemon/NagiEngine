#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log.h"
#include "Input.h"

#include <GLFW/glfw3.h>
#include "PurlemonHazel/Renderer/Renderer.h"

namespace PH {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::instance_ = nullptr;

	Application::Application()
	{
		PH_CORE_ASSERT(!instance_, "Application已经存在！");
		instance_ = this;

		window_ = std::unique_ptr<Window>(Window::Create());
		window_->SetEventCallback(BIND_EVENT_FN(OnEvent));
	
		imgui_layer_ = new ImGuiLayer();
		PushOverlay(imgui_layer_);

	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		layer_stack_.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		layer_stack_.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		// 接收到WindowCloseEvent事件关闭窗口
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// 对所有层进行OnEvent调用
		for (auto it = layer_stack_.end(); it != layer_stack_.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.handled_)
				break;
		}
	}

	void Application::Run()
	{
		while (running_) {
			float time = glfwGetTime(); // TODO: 对不同平台的GetTime
			Timestep timestep(time - last_frame_time_);
			last_frame_time_ = time;

			for (Layer* layer : layer_stack_)
				layer->OnUpdate(timestep);

			imgui_layer_->Begin();
			for (Layer* layer : layer_stack_)
				layer->OnImGuiRender();
			imgui_layer_->End();

			window_->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;
	}
}