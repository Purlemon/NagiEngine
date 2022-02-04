#pragma once

#include "PurlemonHazel/Layer.h"

namespace PurlemonHazel {

	class PH_API ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		float time_ = 0.0f;
	};

}