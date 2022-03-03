#pragma once

#include "PurlemonHazel/Core.h"

namespace PH {

	class PH_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}