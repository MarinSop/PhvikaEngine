#pragma once


#include <EASTL/string.h>
namespace phv {

	enum class EventType {
		None = 0,
		WindowResize, WindowClose,
		KeyPressed, KeyReleased
	};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName()const override { return #type;}

	class Event
	{
	public:
		virtual ~Event() = default;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;

		bool IsHandled = false;

	};


}



