#pragma once

#include "../Core.h"

#include <string>
#include <functional>

namespace PH {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// һ���¼������ж��ַ���
	enum EventCategory
	{
		kNone = 0,
		kEventCategoryApplication = BIT(0),
		kEventCategoryInput = BIT(1),
		kEventCategoryKeyboard = BIT(2),
		kEventCategoryMouse = BIT(3),
		kEventCategoryMouseButton = BIT(4)
	};

	class PH_API Event
	{
	private:
		friend class EventDispatcher; 
	public:
		bool handled_ = false; // �¼��Ƿ񱻴���

		virtual EventType GetEventType()const = 0;
		virtual const char* GetName()const = 0; // only debug
		virtual int GetCategoryFlags()const = 0;
		virtual std::string ToString()const { return GetName(); } // only debug

		// ���ط�0�������������
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	// ��ÿ��Event������ʵ���麯������
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								EventType GetEventType()const override { return GetStaticType(); }\
								const char* GetName()const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) int GetCategoryFlags()const override { return category; }

	// �¼����ȣ�����һ��Event��ʵ����
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) :event_(event){ }
	
		// ��ʵ����ʱ���event_��Tͬ����ʱ�����ô����func������true
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (event_.GetEventType() == T::GetStaticType()) {
				event_.handled_ = func(*(T*)&event_);
				return true;
			}
			return false;
		}
	private:
		Event& event_;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}