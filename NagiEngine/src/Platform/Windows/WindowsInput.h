#pragma once

#include "NagiEngine/Core/Input.h"

namespace Nagi {

	class WindowsInput :public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl()override;
		virtual float GetMouseXImpl()override;
		virtual float GetMouseYImpl() override;
	};

}