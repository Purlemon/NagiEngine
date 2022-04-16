#pragma once

#include "Core.h"

#include <utility>

namespace Nagi {
	// µ¥ÀıÀà
	class Input
	{
	public:
		static bool IsKeyPressed(int key);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}