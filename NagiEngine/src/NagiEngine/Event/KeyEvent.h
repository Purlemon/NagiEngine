#pragma once

#include "Event.h"

#include <sstream>

namespace Nagi {

	class NAGI_API KeyEvent : public Event
	{ // 抽象类
	public:
		int GetKeyCode() const { return key_code_; }

		EVENT_CLASS_CATEGORY(kEventCategoryInput | kEventCategoryKeyboard)
	protected:
		KeyEvent(int key_code)
			:key_code_(key_code){} 
		int key_code_;
	};

	class NAGI_API KeyPressedEvent :public KeyEvent
	{// 键盘按压事件，长按会先输入一次key_code，停顿一下后重复key_code
	public:
		KeyPressedEvent(int key_code,int repeat_count)
			:KeyEvent(key_code),repeat_count_(repeat_count){ }

		int GetRepeatCount()const { return repeat_count_; }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << key_code_ << "(" << repeat_count_ << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeat_count_;
	};

	class NAGI_API KeyReleasedEvent :public KeyEvent
	{
	public:
		KeyReleasedEvent(int key_code)
			:KeyEvent(key_code){ }

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyReleased: " << key_code_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class NAGI_API KeyTypedEvent :public KeyEvent
	{// 键盘按压事件，长按会先输入一次key_code，停顿一下后重复key_code
	public:
		KeyTypedEvent(int key_code)
			:KeyEvent(key_code)
		{
		}

		std::string ToString()const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << key_code_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}