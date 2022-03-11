#pragma once

#include "PurlemonHazel/Core/Core.h"
#include "PurlemonHazel/Core/Log.h"

namespace PH {

	class PH_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}