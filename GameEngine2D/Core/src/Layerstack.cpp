#include "Layerstack.h"

void LayerStack::PushLayer(Layer* layer)
{
	m_layers.emplace(m_layers.begin() + m_LayerInsertIndex, layer);
	m_LayerInsertIndex++;
	layer->OnAttach(); 
	std::cout << layer->GetDebugName() << " has been attached...\n";

}

void LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_layers.begin(), m_layers.begin() + m_LayerInsertIndex, layer);
	std::cout << layer->GetDebugName() << " has been detached...\n";
	layer->OnDettach();
	m_layers.erase(it);
	m_LayerInsertIndex--;

}

void LayerStack::PushOverlay(Layer* overlay)
{
	m_layers.emplace_back(overlay);
	overlay->OnAttach();
	std::cout << overlay->GetDebugName() << " has been attached...\n";

}

void LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(m_layers.begin() + m_LayerInsertIndex, m_layers.end(), overlay);
	overlay->OnDettach();
	m_layers.erase(it);
}

void LayerStack::OnUpdate()
{
	for (auto& layer : m_layers)
	{
		layer->OnUpdate();
		layer->OnImGuiRender();
	}
}

void LayerStack::OnEvent(Event& _event)
{
	//Push event to layers until handled
	for (auto it = m_layers.end(); it != m_layers.begin();)
	{
		(*--it)->OnEvent(_event);
		if (_event.handled)
			break;

	}
}

void LayerStack::FlushLayers()
{
	for (auto layer: m_layers)
	{
		PopLayer(layer);
	}
}
