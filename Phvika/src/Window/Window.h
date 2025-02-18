#pragma once

#include "../Phvika/Core.h"
#include <GLFW/glfw3.h>

class PHV_API Window
{
public:
	Window(const char* title, int width, int height);
	~Window();


	GLFWwindow* GetWindow() const { return m_window; }

private:
	int m_width = 0;
	int m_height = 0;
	GLFWwindow* m_window = nullptr;
};

