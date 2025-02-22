#pragma once
#include <Phvika/Core.h>
#include <vulkan/vulkan.h>

namespace phv {

	class PHV_API VulkanDebug
	{
	public:
		VulkanDebug(const VkInstance instance);
		~VulkanDebug();

		const VkDebugUtilsMessengerEXT getDebugUtilsMessengerEXT();
		static void populateDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugUtilsMessengerInfo);
	private:
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	private:
		const VkInstance m_instance = VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT m_debugUtilsMessenger = VK_NULL_HANDLE;
	};

}

