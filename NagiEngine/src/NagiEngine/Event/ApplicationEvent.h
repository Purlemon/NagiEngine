#pragma once

#include "Event.h"

#include <sstream>

namespace Nagi {

	class NAGI_API WindowResizeEvent :public Event
	{
	public:
		WindowResizeEvent(ng_uint32 width, ng_uint32 height)
			:width_(width),height_(height){ }

		ng_uint32 GetWidth()const { return width_; }
		ng_uint32 GetHeight()const { return height_; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width_ << ", " << height_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
	    EVENT_CLASS_CATEGORY(kEventCategoryApplication)

	private:
		ng_uint32 width_, height_;
	};

	class NAGI_API WindowCloseEvent :public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class NAGI_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class NAGI_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class NAGI_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

}