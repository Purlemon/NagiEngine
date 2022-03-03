#pragma once

#include "Event.h"

#include <sstream>

namespace PH {

	class PH_API  MouseMovedEvent :public Event
	{
	public:
		MouseMovedEvent(float mouse_x,float mouse_y)
			:mouse_x_(mouse_x),mouse_y_(mouse_y){ }

		inline float GetX()const { return mouse_x_; }
		inline float GetY()const { return mouse_y_; }

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

	class PH_API MouseScrolledEvent :public Event
	{
	public:
		MouseScrolledEvent(float x_offset,float y_offset)
			:x_offset_(x_offset),y_offset_(y_offset){ }

		inline float GetXOffset()const { return x_offset_; }
		inline float GetYOffset()const { return y_offset_; }

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

	class PH_API MouseButtonEvent :public Event
	{
	public:
		inline int GetMouseButton()const { return button_; }

		EVENT_CLASS_CATEGORY(kEventCategoryInput | kEventCategoryMouse | kEventCategoryMouseButton)

	protected:
		MouseButtonEvent(int button)
			:button_(button){ }

		int button_;
	};

	class PH_API MouseButtonPressedEvent :public MouseButtonEvent
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

	class PH_API MouseButtonReleasedEvent :public MouseButtonEvent
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

