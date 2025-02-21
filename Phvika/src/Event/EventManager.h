#pragma once

#include "Phvika/Core.h"
#include <EASTL/functional.h>
#include <EASTL/queue.h>
#include <EASTL/unordered_map.h>
#include <EASTL/vector.h>
#include  <EASTL/string.h>
#include "EventHandler.h"

namespace phv {

	class EventManager
	{
	public:
		EventManager() = default;
		EventManager(const EventManager&) = delete;
		const EventManager& operator=(const EventManager&) = delete;

		void Subscribe(EventType eventType, Unique<IEventHandlerWrapper>&& handler);
		//TO FIX
		//void Unsubscribe(eastl::unique_ptr<IEventHandlerWrapper> handler);
		void TriggerEvent(Event& e);
		void QueueEvent(Unique<Event>&& event);
		void DispatchEvents();
		void Shutdown();


	private:
		eastl::queue<Unique<Event>> m_queuedEvents;
		eastl::unordered_map<EventType, eastl::vector<Unique<IEventHandlerWrapper>>> m_handlers;
		
	};

	extern EventManager g_eventManager;

	inline void Subscribe(Unique<IEventHandlerWrapper> callback)
	{	
		g_eventManager.Subscribe(callback->GetType(), std::move(callback));
	}

	//iMPLEMENT UNSUBSCRIBE

	inline void TriggerEvent(Event& e)
	{
		g_eventManager.TriggerEvent(e);
	}

	inline void QueueEvent(Unique<Event>&& e)
	{
		g_eventManager.QueueEvent(std::forward<Unique<Event>>(e));
	}

	inline void Shutdown()
	{
		g_eventManager.Shutdown();
	}
}

