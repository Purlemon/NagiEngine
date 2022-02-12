#pragma once

#include "Core.h"
#include "Event/Event.h"

#include <sstream>

namespace PurlemonHazel {

	class PH_API Layer
	{
	public:
		Layer(const std::string& debug_name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(){}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName()const { return debug_name_; }

	protected:
		std::string debug_name_;
	};

}