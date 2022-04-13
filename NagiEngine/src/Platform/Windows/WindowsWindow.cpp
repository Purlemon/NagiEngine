#include "WindowsWindow.h"
#include "NagiEngine/Core/Log.h"

#include "NagiEngine/Event/ApplicationEvent.h"
#include "NagiEngine/Event/KeyEvent.h"
#include "NagiEngine/Event/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Nagi {

	static bool sGLFWInitialized = false;

	static void GLFWErrorCallback(int error_code, const char* description)
	{
		NAGI_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}


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

		NAGI_CORE_INFO("正在创建窗口 {0} ({1}, {2})", props.title, props.width, props.height);

		// 创建唯一窗口
		if (!sGLFWInitialized) {
			int success = glfwInit();
			NAGI_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			sGLFWInitialized = true;
		}

		window_ = glfwCreateWindow((int)props.width, (int)props.height, data_.title.c_str(), nullptr, nullptr);
		
		context_ = new OpenGLContext(window_);
		context_->Init();

		glfwSetWindowUserPointer(window_, &data_);
		SetVSync(true);

		// 设置GLFW回调函数
		glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.event_callback(event); // 调用绑定的Application::OnEvent函数
		});

		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.event_callback(event);
		});

		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: 
				{
					KeyPressedEvent event(key, 0);
					data.event_callback(event);
					break;
				}
				case GLFW_RELEASE: 
				{
					KeyReleasedEvent event(key);
					data.event_callback(event);
					break;
				}
				case GLFW_REPEAT: 
				{
					KeyPressedEvent event(key, 1); // 暂时这样
					data.event_callback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(window_, [](GLFWwindow* window,ng_uint32 keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.event_callback(event);
			});

		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: 
				{
					MouseButtonPressedEvent event(button);
					data.event_callback(event);
					break;
				}
				case GLFW_RELEASE: 
				{
					MouseButtonReleasedEvent event(button);
					data.event_callback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(window_, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.event_callback(event);
		});

		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xpos, (float)ypos);
			data.event_callback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window_);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		context_->SwapBuffers();
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