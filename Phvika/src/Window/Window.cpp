#include "Window.h"

Window::Window(const char* title, int width, int height)
	: m_width(width), m_height(height)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
}

