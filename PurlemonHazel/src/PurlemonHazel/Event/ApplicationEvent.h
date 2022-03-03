#pragma once

#include "Event.h"

#include <sstream>

namespace PH {

	class PH_API WindowResizeEvent :public Event
	{
	public:
		WindowResizeEvent(unsigned int width,unsigned int height)
			:width_(width),height_(height){ }

		inline unsigned int GetWidth()const { return width_; }
		inline unsigned int GetHeight()const { return height_; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width_ << ", " << height_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
	    EVENT_CLASS_CATEGORY(kEventCategoryApplication)

	private:
		unsigned int width_, height_;
	};

	class PH_API WindowCloseEvent :public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class PH_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class PH_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

	class PH_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(kEventCategoryApplication)
	};

}