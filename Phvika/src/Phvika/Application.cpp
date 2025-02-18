#include "Application.h"

namespace phv {

	phv::Application::Application()
	{
	}

	phv::Application::~Application()
	{
	}

	void Application::init()
	{
		m_window.reset(new Window("Application", 600, 800));
	}

	void Application::loop()
	{
		while (!glfwWindowShouldClose(m_window.get()->GetWindow()))
		{
			glfwPollEvents();
		}
	}

}
