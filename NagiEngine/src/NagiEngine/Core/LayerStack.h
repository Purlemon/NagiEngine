#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Nagi {

	class NAGI_API LayerStack
	{
	public:
		using LayersIter = std::vector<Layer*>::iterator;

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);	  // ͷ����Ԫ��
		void PushOverlay(Layer* overlay); // β����Ԫ��
		void PopLayer(Layer* layer);      
		void PopOverlay(Layer* overlay); 

		LayersIter begin() { return layers_.begin(); }
		LayersIter end() { return layers_.end(); }

	private:
		std::vector<Layer*>layers_;
		ng_uint32 layer_insert_index_ = 0;;
	};

}