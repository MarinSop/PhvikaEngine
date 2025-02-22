#pragma once

#include "Phvika/Core.h"
#include <vulkan/vulkan.h>

namespace phv {

	class VulkanPhysicalDevice
	{
	public:
		VulkanPhysicalDevice();
		~VulkanPhysicalDevice();


	const VkPhysicalDevice GetPhysicalDevice();
	private:
		const VkInstance m_instance = VK_NULL_HANDLE;
		VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	};

}

