#pragma once

#include <EASTL/functional.h>
#include <EASTL/queue.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/unordered_map.h>
#include <EASTL/vector.h>
#include  <EASTL/string.h>
#include "EventHandler.h"

namespace phv {

	//struct EnumClassHash
	//{
	//	template <typename T>
	//	std::size_t operator()(T t) const
	//	{
	//		return static_cast<std::size_t>(t);
	//	}
	//};

	class EventManager
	{
	public:
		EventManager() = default;
		EventManager(const EventManager&) = delete;
		const EventManager& operator=(const EventManager&) = delete;

		void Subscribe(EventType eventType, eastl::unique_ptr<IEventHandlerWrapper>&& handler);
		//TO FIX
		//void Unsubscribe(eastl::unique_ptr<IEventHandlerWrapper> handler);
		void TriggerEvent(Event& e);
		void QueueEvent(eastl::unique_ptr<Event>&& event);
		void DispatchEvents();
		void Shutdown();


	private:
		eastl::queue<eastl::unique_ptr<Event>> m_queuedEvents;
		eastl::unordered_map<EventType, eastl::vector<eastl::unique_ptr<IEventHandlerWrapper>>> m_handlers;
		
	};

	extern EventManager g_eventManager;

	inline void Subscribe(eastl::unique_ptr<IEventHandlerWrapper> callback)
	{	
		g_eventManager.Subscribe(callback->GetType(), std::move(callback));
	}

	//iMPLEMENT UNSUBSCRIBE

	inline void TriggerEvent(Event& e)
	{
		g_eventManager.TriggerEvent(e);
	}

	inline void QueueEvent(eastl::unique_ptr<Event>&& e)
	{
		g_eventManager.QueueEvent(std::forward<eastl::unique_ptr<Event>>(e));
	}

	inline void Shutdown()
	{
		g_eventManager.Shutdown();
	}
}

