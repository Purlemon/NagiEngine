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
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { block_events_ = block; }

	private:
		bool block_events_ = true;
		float time_ = 0.0f;
	};

}