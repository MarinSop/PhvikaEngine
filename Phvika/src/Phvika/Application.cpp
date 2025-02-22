#include "Application.h"
#include "../Event/WindowResizeEvent.h"
#include "../Event/EventManager.h"

namespace phv {

	phv::Application::Application()
	{
		m_window = MakeUnique<Window>("Application", 600, 800);
	}

	phv::Application::~Application()
	{
		g_eventManager.Shutdown();
	}

	void Application::init()
	{
	}

	void Application::loop()
	{
		while (!glfwWindowShouldClose(m_window.get()->GetWindow()))
		{
			glfwPollEvents();
			g_eventManager.DispatchEvents();
		}
	}

}
