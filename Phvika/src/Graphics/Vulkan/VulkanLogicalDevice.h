#pragma once
#include <Phvika/Core.h>
#include <vulkan/vulkan.h>
#include <EASTL/optional.h>

namespace phv {

	class PHV_API VulkanLogicalDevice
	{
	public:
		VulkanLogicalDevice(const VkPhysicalDevice physicalDevice, const VkSurfaceKHR surface);



	private:
		void FindQueueFamilyIndices();
		void CreateLogicalDevice();

	private:
		const VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
		const VkSurfaceKHR m_surface = VK_NULL_HANDLE;
		VkDevice m_logicalDevice = VK_NULL_HANDLE;

		VkQueueFlags m_supportedQueues{};
		eastl::optional<uint32_t> graphicsFamily;
		eastl::optional<uint32_t> presentFamily;
		eastl::optional<uint32_t> transferFamily;
		eastl::optional<uint32_t> computeFamily;
	};

}

