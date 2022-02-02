#pragma once

#include "Event.h"

#include <sstream>

namespace PurlemonHazel {

	class PH_API KeyEvent : public Event
	{ // ������
	public:
		inline int GetKeyCode() const { return key_code_; }

		EVENT_CLASS_CATEGORY(kEventCategoryInput | kEventCategoryKeyboard)
	protected:
		KeyEvent(int key_code)
			:key_code_(key_code){} 
		int key_code_;
	};

	class PH_API KeyPressedEvent :public KeyEvent
	{// ���̰�ѹ�¼���������������һ��key_code��ͣ��һ�º��ظ�key_code
	public:
		KeyPressedEvent(int key_code,int repeat_count)
			:KeyEvent(key_code),repeat_count_(repeat_count){ }

		inline int GetRepeatCount()const { return repeat_count_; }

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

	class PH_API KeyReleasedEvent :public KeyEvent
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

}