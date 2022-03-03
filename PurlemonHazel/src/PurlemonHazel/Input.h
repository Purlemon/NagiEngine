#pragma once

#include "Core.h"

#include <utility>

namespace PH {
	// 单例类
	class PH_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return instance_->IsKeyPressedImpl(keycode); }
	
		inline static bool IsMouseButtonPressed(int button) { return instance_->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return instance_->GetMousePositionImpl(); }
		inline static float GetMouseX() { return instance_->GetMouseXImpl(); }
		inline static float GetMouseY() { return instance_->GetMouseYImpl(); }
	protected:
		// 子类实现接口
		virtual bool IsKeyPressedImpl(int keycode) = 0; 
	
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* instance_;
	};

}