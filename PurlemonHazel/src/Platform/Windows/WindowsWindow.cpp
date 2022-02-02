#include "WindowsWindow.h"
#include "../../PurlemonHazel/Log.h"

namespace PurlemonHazel {

	static bool sGLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}
	
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		data_.title = props.title;
		data_.width = props.width;
		data_.height = props.height;

		PH_CORE_INFO("正在创建窗口 {0} ({1}, {2})", props.title, props.width, props.height);

		// 创建唯一窗口
		if (!sGLFWInitialized) {
			int success = glfwInit();
			PH_CORE_ASSERT(success, "Could not intialize GLFW!");
			sGLFWInitialized = true;
		}

		window_ = glfwCreateWindow((int)props.width, (int)props.height, data_.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window_);
		glfwSetWindowUserPointer(window_, &data_);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window_);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window_);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1); // 等待刷新后再交换缓冲区实现垂直同步
		}
		else {
			glfwSwapInterval(0); // 立刻交换缓冲区
		}

		data_.vsync = enabled;
	}

	bool WindowsWindow::IsVSync()const
	{
		return data_.vsync;
	}

}