#pragma once

#include "PurlemonHazel/Core.h"
#include "PurlemonHazel/Log.h"

namespace PH {

	class PH_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}