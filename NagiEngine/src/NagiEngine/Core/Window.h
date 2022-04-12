#pragma once

#include "Core.h"
#include "NagiEngine/Event/Event.h"

#include <functional>

namespace Nagi {

	// ���ڴ洢��ʼ��������Ϣ
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

	// ���ڽӿڣ�����ÿ��ƽ̨ʵ��
	class NAGI_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual ph_uint32 GetWidth()const = 0;
		virtual ph_uint32 GetHeight()const = 0;

		// ��������
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;// ���ô�ֱͬ��
		virtual bool IsVSync()const = 0; 

		virtual void* GetNativeWindow()const = 0; // ����void�Ա�ʹ�ò�ͬwindow��

		static Window* Create(const WindowProps& props = WindowProps());

	};

}