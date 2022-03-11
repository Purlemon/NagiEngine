#pragma once

#include "PurlemonHazel/Core/Layer.h"

#include "PurlemonHazel/Event/MouseEvent.h"
#include "PurlemonHazel/Event/KeyEvent.h"
#include "PurlemonHazel/Event/ApplicationEvent.h"

namespace PH {

	class PH_API ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float time_ = 0.0f;
	};

}