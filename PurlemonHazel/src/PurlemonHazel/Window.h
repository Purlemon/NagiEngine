#pragma once

#include "../PurlemonHazel/Core.h"
#include "Event/Event.h"

#include <functional>

namespace PurlemonHazel {

	// ���ڴ洢��ʼ��������Ϣ
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

	// ���ڽӿڣ�����ÿ��ƽ̨ʵ��
	class PH_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth()const = 0;
		virtual unsigned int GetHeight()const = 0;

		// ��������
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;// ���ô�ֱͬ��
		virtual bool IsVSync()const = 0; 

		static Window* Create(const WindowProps& props = WindowProps());

	};

}