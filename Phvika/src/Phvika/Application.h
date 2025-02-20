#pragma once
#include "Log.h"
#include "Core.h"
#include "../Window/Window.h"
#include<EASTL/unique_ptr.h>

namespace phv {

	class PHV_API Application
	{
	public:
		Application();
		virtual ~Application();

		void init();

		void loop();



	private:
		eastl::unique_ptr<phv::Window> m_window;
	};

	Application* CreateApplication();

}

