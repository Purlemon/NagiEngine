#pragma once

#include "PurlemonHazel/Window.h"
#include "PurlemonHazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace PH {

	class WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate()override;

		inline unsigned int GetWidth() const override { return data_.width; }
		inline unsigned int GetHeight() const override { return data_.height; }

		inline void* GetNativeWindow()const override { return window_; }

		// ¥∞ø⁄ Ù–‘
		inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			data_.event_callback = callback;
		}

		void SetVSync(bool enabled)override;
		bool IsVSync()const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* window_;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vsync;

			EventCallbackFn event_callback;
		};

		WindowData data_;
		GraphicsContext* context_;
	};

}