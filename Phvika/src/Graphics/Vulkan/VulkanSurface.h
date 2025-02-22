#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Phvika/Core.h"
#include <vulkan/vulkan.h>

namespace phv {

	class PHV_API VulkanSurface
	{
	public:
		VulkanSurface(const VkInstance instance, GLFWwindow* window);
		~VulkanSurface();

		const VkSurfaceKHR GetSurface();
	private:
		GLFWwindow* m_window = nullptr;
		const VkInstance m_instance = VK_NULL_HANDLE;
		VkSurfaceKHR m_surface = VK_NULL_HANDLE;
	};

}

