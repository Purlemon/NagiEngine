#include "Application.h"
#include "PurlemonHazel/Event/ApplicationEvent.h"
#include "Log.h"
#include "Input.h"

#include <GLFW/glfw3.h>
#include "PurlemonHazel/Renderer/Renderer.h"

namespace PH {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::instance_ = nullptr;

	Application::Application()
	{
		PH_CORE_ASSERT(!instance_, "Application�Ѿ����ڣ�");
		instance_ = this;

		window_ = std::unique_ptr<Window>(Window::Create());
		window_->SetEventCallback(BIND_EVENT_FN(OnEvent));
	
		Renderer::Init();

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
		
		EventDispatcher dispatcher(e);
		// ���յ�WindowCloseEvent�¼��رմ���
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		// �����в����OnEvent����
		for (auto it = layer_stack_.end(); it != layer_stack_.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.handled_)
				break;
		}
	}

	void Application::Run()
	{
		while (running_) {
			float time = glfwGetTime(); // TODO: �Բ�ͬƽ̨��GetTime
			Timestep timestep(time - last_frame_time_);
			last_frame_time_ = time;

			if (!minimized_) { // ��С��������
				for (Layer* layer : layer_stack_)
					layer->OnUpdate(timestep);
			}

			imgui_layer_->Begin();
			for (Layer* layer : layer_stack_)
				layer->OnImGuiRender();
			imgui_layer_->End();

			window_->OnUpdate();
		}
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			minimized_ = true;
			return false;
		}

		minimized_ = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;
	}
}