#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace PH {

	class PH_API LayerStack
	{
	public:
		using LayersIter = std::vector<Layer*>::iterator;

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);	  // 头插入元素
		void PushOverlay(Layer* overlay); // 尾插入元素
		void PopLayer(Layer* layer);      
		void PopOverlay(Layer* overlay); 

		inline LayersIter begin() { return layers_.begin(); }
		inline LayersIter end() { return layers_.end(); }

	private:
		std::vector<Layer*>layers_;
		unsigned int layer_insert_index_ = 0;;
	};

}