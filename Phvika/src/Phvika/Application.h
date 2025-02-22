#pragma once
#include "Window/Window.h"
#include "Log.h"
#include "Core.h"

namespace phv {

	class PHV_API Application
	{
	public:
		Application();
		virtual ~Application();

		void init();

		void loop();



	private:
		Unique<Window> m_window;
	};

	Application* CreateApplication();

}

