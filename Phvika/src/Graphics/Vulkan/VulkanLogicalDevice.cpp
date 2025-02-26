#include "VulkanLogicalDevice.h"
#include "Graphics/Vulkan/VulkanConstants.h"
#include <EASTL/vector.h>

namespace phv {

	VulkanLogicalDevice::VulkanLogicalDevice(const VkPhysicalDevice physicalDevice, const VkSurfaceKHR surface)
		:m_physicalDevice(physicalDevice), m_surface(surface)
	{
		FindQueueFamilyIndices();
		CreateLogicalDevice();
	}

	void VulkanLogicalDevice::FindQueueFamilyIndices()
	{
		uint32_t queueFamilyPropertyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyPropertyCount, nullptr);

		eastl::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyPropertyCount, queueFamilyProperties.data());

		for (uint32_t i = 0; i < queueFamilyPropertyCount; i++)
		{
			if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				graphicsFamily = i;
				m_supportedQueues |= VK_QUEUE_GRAPHICS_BIT;
			}
			if (queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
			{
				computeFamily = i;
				m_supportedQueues |= VK_QUEUE_COMPUTE_BIT;
			}
			if (queueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				transferFamily = i;
				m_supportedQueues |= VK_QUEUE_TRANSFER_BIT;
			}
			VkBool32 hasPresentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, i, m_surface, &hasPresentSupport);
			if (hasPresentSupport)
			{
				presentFamily = i;
			}
		}

		PHV_CORE_ASSERT(!graphicsFamily.has_value(), "Failed to find graphics queue family!");

	}

	void VulkanLogicalDevice::CreateLogicalDevice()
	{
		eastl::vector<VkDeviceQueueCreateInfo> queueInfos;
		float queuePriority = 1.0f;
		if (graphicsFamily.has_value())
		{
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueCount = 1;
			queueInfo.queueFamilyIndex = graphicsFamily.value();
			queueInfo.pQueuePriorities = &queuePriority;
			queueInfos.emplace_back(queueInfo);
		}
		if (presentFamily.has_value() &&
			presentFamily.value() != graphicsFamily.value())
		{
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueCount = 1;
			queueInfo.queueFamilyIndex = presentFamily.value();
			queueInfo.pQueuePriorities = &queuePriority;
			queueInfos.emplace_back(queueInfo);
		}
		if (computeFamily.has_value() &&
			computeFamily.value() != graphicsFamily.value() &&
			computeFamily.value() != presentFamily.value())
		{
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueCount = 1;
			queueInfo.queueFamilyIndex = computeFamily.value();
			queueInfo.pQueuePriorities = &queuePriority;
			queueInfos.emplace_back(queueInfo);
		}
		if (transferFamily.has_value() &&
			transferFamily.value() != graphicsFamily.value() &&
			transferFamily.value() != presentFamily.value() &&
			transferFamily.value() != computeFamily.value())
		{
			VkDeviceQueueCreateInfo queueInfo{};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueCount = 1;
			queueInfo.queueFamilyIndex = transferFamily.value();
			queueInfo.pQueuePriorities = &queuePriority;
			queueInfos.emplace_back(queueInfo);
		}

		VkPhysicalDeviceFeatures enabledFeatures{};

		VkDeviceCreateInfo deviceInfo{};
		deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		deviceInfo.ppEnabledExtensionNames = deviceExtensions.data();
		deviceInfo.queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size());
		deviceInfo.pQueueCreateInfos = queueInfos.data();
		deviceInfo.pEnabledFeatures = &enabledFeatures;
		#ifdef PHV_DEBUG
			deviceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			deviceInfo.ppEnabledLayerNames = validationLayers.data();
		#else
			deviceInfo.enabledLayercount = 0;
		#endif

		VkResult result = vkCreateDevice(m_physicalDevice, &deviceInfo, nullptr, &m_logicalDevice);
		PHV_CORE_ASSERT(result != VK_SUCCESS, "Failed to create logical device!");
	}

}
