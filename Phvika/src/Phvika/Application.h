#pragma once
#include "Log.h"
#include "Core.h"
#include "../Window/Window.h"

namespace phv {

	class PHV_API Application
	{
	public:
		Application();
		virtual ~Application();

		void init();

		void loop();



	private:
		Unique<phv::Window> m_window;
	};

	Application* CreateApplication();

}

