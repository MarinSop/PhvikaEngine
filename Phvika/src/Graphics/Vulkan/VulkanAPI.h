#pragma once
#include "Phvika/Core.h"
#include "VulkanInstance.h"
#include "VulkanDebug.h"
#include "VulkanSurface.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"

#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>

namespace phv {

	class PHV_API VulkanAPI
	{
	public:
		VulkanAPI(GLFWwindow* window);


	private:
		GLFWwindow* m_window;
		Unique<VulkanInstance> m_instance;
		Unique<VulkanDebug> m_debug;
		Unique<VulkanSurface> m_surface;
		Unique<VulkanPhysicalDevice> m_physicalDevice;
		Unique<VulkanLogicalDevice> m_logicalDevice;
	};

}

