#pragma once

#include "NagiEngine/Core/Layer.h"

#include "NagiEngine/Event/MouseEvent.h"
#include "NagiEngine/Event/KeyEvent.h"
#include "NagiEngine/Event/ApplicationEvent.h"

namespace Nagi {

	class NAGI_API ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float time_ = 0.0f;
	};

}