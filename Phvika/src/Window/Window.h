#pragma once
#define GLFW_INCLUDE_VULKAN
#include "Phvika/Core.h"
#include <GLFW/glfw3.h>
#include "Graphics/Vulkan/VulkanAPI.h"

namespace phv {

	class PHV_API Window
	{
	public:
		Window(const char* title, int width, int height);
		~Window();


		GLFWwindow* GetWindow() const { return m_window; }

	private:
		int m_width = 0;
		int m_height = 0;
		Shared<VulkanAPI> m_vulkanAPI;
		GLFWwindow* m_window = nullptr;
	};
}
