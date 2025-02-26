#include "VulkanPhysicalDevice.h"
#include <EASTL/map.h>

namespace phv{
	VulkanPhysicalDevice::VulkanPhysicalDevice(const VkInstance instance, const VkSurfaceKHR surface)
		:m_instance(instance), m_surface(surface)
	{
		uint32_t physicalDevicesCount = 0;

		vkEnumeratePhysicalDevices(m_instance, &physicalDevicesCount, nullptr);

		eastl::vector<VkPhysicalDevice> physicalDevices(physicalDevicesCount);
		vkEnumeratePhysicalDevices(m_instance, &physicalDevicesCount, physicalDevices.data());

		FindSuitableDevice(physicalDevices);
		PHV_CORE_ASSERT(physicalDevicesCount == 0, "Failed tp find GPUs that support Vulkan.");


	}
	void VulkanPhysicalDevice::FindSuitableDevice(const eastl::vector<VkPhysicalDevice>& physicalDevices)
	{
		eastl::map<uint32_t, VkPhysicalDevice> ratedPhysicalDevices;
		for (const auto& device : physicalDevices)
		{
			uint32_t score = RateDevice(device);
			ratedPhysicalDevices.insert(eastl::make_pair(score, device));
		}
		PHV_CORE_ASSERT(ratedPhysicalDevices.rbegin()->first <= 0, "failed to find suitabel GPU!");
		m_physicalDevice = ratedPhysicalDevices.rbegin()->second;
	}
	uint32_t VulkanPhysicalDevice::RateDevice(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(device, &properties);
		VkPhysicalDeviceMemoryProperties memoryProperties;
		vkGetPhysicalDeviceMemoryProperties(device, &memoryProperties);
		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(device, &features);


		uint32_t score = 0;
		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			score += 1000;
		}
		score += properties.limits.maxImageDimension2D;

		for (uint32_t i = 0; i < memoryProperties.memoryHeapCount; i++)
		{
			if(memoryProperties.memoryHeaps[i].flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
			{
				score += memoryProperties.memoryHeaps[i].size / (1024 * 1024 * 1024); // in GB
			}
		}

		if (features.geometryShader)
		{
			score += 100;
		}

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		eastl::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());

		bool hasGraphicsQueue = false;
		bool hasPresentQueue = false;

		for (uint32_t i = 0; i < queueFamilyCount;i++)
		{
			if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				hasGraphicsQueue = true;
			}
			VkBool32 hasPresentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, static_cast<uint32_t>(i), m_surface, &hasPresentSupport);
			if (hasPresentSupport)
			{
				hasPresentQueue = true;
			}
		}
		if(hasGraphicsQueue && hasPresentQueue)
		{
			score += 500;
		}


		return score;
	}
}
