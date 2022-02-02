#pragma once

#include "../PurlemonHazel/Core.h"
#include "Event/Event.h"

#include <functional>

namespace PurlemonHazel {

	// 用于存储初始化窗口信息
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& t = "PurlemonHazel",
			unsigned int w = 1280,
			unsigned int h =720)
			:title(t),width(w),height(h){ }
			
	};

	// 窗口接口，将在每个平台实现
	class PH_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth()const = 0;
		virtual unsigned int GetHeight()const = 0;

		// 窗口属性
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;// 设置垂直同步
		virtual bool IsVSync()const = 0; 

		static Window* Create(const WindowProps& props = WindowProps());

	};

}