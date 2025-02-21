#include "EventManager.h"
#include "EASTL/utility.h"

namespace phv {

	EventManager g_eventManager;

	void EventManager::Subscribe(EventType eventType, Unique<IEventHandlerWrapper>&& handler)
	{
		m_handlers[eventType].emplace_back(std::move(handler));
	}

	// TO FIX
	//void EventManager::Unsubscribe(eastl::unique_ptr<IEventHandlerWrapper> handler)
	//{
	//	auto handlers = m_handlers.find(handler->GetType());
	//	if (handlers != m_handlers.end())
	//	{
	//		for (auto it = handlers->second.begin(); it != handlers->second.end(); it++)
	//		{
	//			if (it->get()->GetType() == handler->GetType())
	//			{
	//				handlers->second.erase(it);
	//				return;
	//			}
	//		}
	//	}
	//}
	void EventManager::TriggerEvent(Event& e)
	{
		auto it = m_handlers.find(e.GetEventType());
		if (it != m_handlers.end())
		{
			for (auto& handler : it->second)
			{
				handler->Execute(e);
			}
		}
	}
	void EventManager::QueueEvent(Unique<Event>&& event)
	{
		m_queuedEvents.emplace_back(std::move(event));
	}
	void EventManager::DispatchEvents()
	{
		while (!m_queuedEvents.empty())
		{
			auto event = std::move(m_queuedEvents.front());
			m_queuedEvents.pop();
			TriggerEvent(*event);
		}
	}
	void EventManager::Shutdown()
	{
		eastl::queue<Unique<Event>> clear;
		eastl::swap(m_queuedEvents, clear);
		m_handlers.clear();
	}
}