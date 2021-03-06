#include "ngpch.h"

#include "LayerStack.h"

namespace Nagi {

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers_)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers_.emplace(layers_.begin() + layer_insert_index_, layer);
		layer_insert_index_++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers_.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers_.begin(), layers_.end(), layer);
		if (it != layers_.end()) {
			layers_.erase(it);
			--layer_insert_index_;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layers_.begin(), layers_.end(), overlay);
		if (it != layers_.end()) {
			layers_.erase(it);
		}
	}

}