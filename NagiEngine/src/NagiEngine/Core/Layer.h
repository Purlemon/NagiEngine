#pragma once

#include "Core.h"
#include "Timestep.h"
#include "NagiEngine/Event/Event.h"

#include <sstream>

namespace Nagi {

	class NAGI_API Layer
	{
	public:
		Layer(const std::string& debug_name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(Timestep ts){}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName()const { return debug_name_; }

	protected:
		std::string debug_name_;
	};

}