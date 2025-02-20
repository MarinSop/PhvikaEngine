#include "Window.h"
#include "../Event/WindowResizeEvent.h"
#include "../Event/EventManager.h"
#include "EASTL/unique_ptr.h"
#include "../Phvika/Log.h"

namespace phv {

	void WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		WindowResizeEvent event(width, height);
		TriggerEvent(event);
	}

	Window::Window(const char* title, int width, int height)
		: m_width(width), m_height(height)
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
		if (!m_window)
		{
			//std::runtime_error("Failed to create window!");
		}
		phv::Subscribe(eastl::make_unique<EventHandlerWrapper<WindowResizeEvent>>([](const WindowResizeEvent& e){
				//do stuff when resize
			}));

		glfwSetWindowSizeCallback(m_window, WindowSizeCallback);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
	}

}
