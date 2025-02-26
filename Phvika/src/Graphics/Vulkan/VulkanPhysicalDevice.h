#pragma once

#include "Phvika/Core.h"
#include <EASTL/vector.h>
#include <vulkan/vulkan.h>

namespace phv {

	class PHV_API VulkanPhysicalDevice
	{
	public:
		VulkanPhysicalDevice(const VkInstance instance, const VkSurfaceKHR surface);
		~VulkanPhysicalDevice() = default;


		const VkPhysicalDevice GetPhysicalDevice() { return m_physicalDevice; };

	private:
		void FindSuitableDevice(const eastl::vector<VkPhysicalDevice>& physicalDevices);
		uint32_t RateDevice(VkPhysicalDevice device);


	private:
		const VkSurfaceKHR m_surface = VK_NULL_HANDLE;
		const VkInstance m_instance = VK_NULL_HANDLE;
		VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
	};

}

