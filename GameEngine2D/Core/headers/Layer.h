#pragma once
#include "Event.h"

class Layer
{
	public:
		Layer(const std::string& name = "LAYER_TEST");
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDettach() {};
		virtual void OnImGuiRender() {};

		virtual void OnUpdate(){}
		virtual void OnEvent(Event& _event){}

		inline const std::string& GetDebugName()const {
			return m_debugname;
		}
	protected:
		std::string m_debugname;	
};