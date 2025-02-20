#pragma once

#include "Event.h"
#include <EASTL/functional.h>

namespace phv {

	template<typename E>
	using EventHandler = eastl::function<void(const E& e)>;

	class IEventHandlerWrapper
	{
	public:
		void Execute(Event& e)
		{
			Call(e);
		}
		virtual ~IEventHandlerWrapper() = default;

		virtual EventType GetType() const = 0;
		virtual bool IsDestroyOnSuccess() const = 0;

	private:
		virtual void Call(const Event& e) const = 0;
	};

	template<typename E>
	class EventHandlerWrapper : public IEventHandlerWrapper
	{
	public:
		explicit EventHandlerWrapper(const EventHandler<E>& handler, const bool destroyOnSuccess = false)
			: m_handler(handler), m_handlerType(E::GetStaticType()), m_destroyOnSuccess(destroyOnSuccess) {
			
		}

	private:

		EventType GetType() const override { return m_handlerType; }
		bool IsDestroyOnSuccess() const override { return m_destroyOnSuccess; }

		void Call(const Event& e) const override
		{
			if (e.GetEventType() == E::GetStaticType())
			{
				m_handler(static_cast<const E&>(e));
			}
		}

		EventHandler<E> m_handler;
		EventType m_handlerType;
		bool m_destroyOnSuccess = false;
	};


}