#pragma once
#include "Phvika/Core.h"
#include "VulkanInstance.h"
#include "VulkanDebug.h"
#include "VulkanSurface.h"
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
	};

}

