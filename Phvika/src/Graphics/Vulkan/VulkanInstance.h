#pragma once
#include "Phvika/Core.h"
#include "vulkan/vulkan.h"

namespace phv {

	class PHV_API VulkanInstance
	{
	public:
		VulkanInstance();
		~VulkanInstance();

		const VkInstance GetInstance();

	private:
		VkInstance m_instance = VK_NULL_HANDLE;
	};

}

