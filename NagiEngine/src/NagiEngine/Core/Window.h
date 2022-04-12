#pragma once

#include "Core.h"
#include "NagiEngine/Event/Event.h"

#include <functional>

namespace Nagi {

	// 用于存储初始化窗口信息
	struct WindowProps
	{
		std::string title;
		ph_uint32 width;
		ph_uint32 height;

		WindowProps(const std::string& t = "NagiEngine",
			ph_uint32 w = 1280,
			ph_uint32 h =720)
			:title(t),width(w),height(h){ }
			
	};

	// 窗口接口，将在每个平台实现
	class NAGI_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual ph_uint32 GetWidth()const = 0;
		virtual ph_uint32 GetHeight()const = 0;

		// 窗口属性
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;// 设置垂直同步
		virtual bool IsVSync()const = 0; 

		virtual void* GetNativeWindow()const = 0; // 返回void以便使用不同window库

		static Window* Create(const WindowProps& props = WindowProps());

	};

}