#pragma once

#include "NagiEngine/Core/Window.h"
#include "NagiEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Nagi {

	class WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate()override;

		ng_uint32 GetWidth() const override { return data_.width; }
		ng_uint32 GetHeight() const override { return data_.height; }

		void* GetNativeWindow()const override { return window_; }

		// ¥∞ø⁄ Ù–‘
		void SetEventCallback(const EventCallbackFn& callback) override
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
			ng_uint32 width, height;
			bool vsync;

			EventCallbackFn event_callback;
		};

		WindowData data_;
		GraphicsContext* context_;
	};

}