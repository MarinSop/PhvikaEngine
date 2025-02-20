#pragma once

#include "Event.h"

namespace phv {

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_width(width), m_height(height) {}

		EVENT_CLASS_TYPE(WindowResize)


	private:

		uint32_t m_width = 0;
		uint32_t m_height = 0;


	};

}
