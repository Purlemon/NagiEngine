#pragma once

#include "Event.h"

#include <sstream>

namespace Nagi {

	class NAGI_API  MouseMovedEvent :public Event
	{
	public:
		MouseMovedEvent(float mouse_x,float mouse_y)
			:mouse_x_(mouse_x),mouse_y_(mouse_y){ }

		float GetX()const { return mouse_x_; }
		float GetY()const { return mouse_y_; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouse_x_ << ", " << mouse_y_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(kEventCategoryInput | kEventCategoryMouse)
	private:
		float mouse_x_, mouse_y_;
	};

	class NAGI_API MouseScrolledEvent :public Event
	{
	public:
		MouseScrolledEvent(float x_offset,float y_offset)
			:x_offset_(x_offset),y_offset_(y_offset){ }

		float GetXOffset()const { return x_offset_; }
		float GetYOffset()const { return y_offset_; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << x_offset_ << ", " << y_offset_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(kEventCategoryInput | kEventCategoryMouse)

	private:
		float x_offset_, y_offset_;
	};

	class NAGI_API MouseButtonEvent :public Event
	{
	public:
		int GetMouseButton()const { return button_; }

		EVENT_CLASS_CATEGORY(kEventCategoryInput | kEventCategoryMouse | kEventCategoryMouseButton)

	protected:
		MouseButtonEvent(int button)
			:button_(button){ }

		int button_;
	};

	class NAGI_API MouseButtonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button){ }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class NAGI_API MouseButtonReleasedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button)
		{
		}
		
		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}

