#pragma once

#include "NagiEngine/Core/Core.h"
#include "NagiEngine/Core/Log.h"

namespace Nagi {

	class NAGI_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

}