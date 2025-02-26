#include "VulkanDebug.h"
#include <EASTL/vector.h>
#include "Graphics/Vulkan/VulkanConstants.h"

namespace phv {

	VKAPI_ATTR VkBool32 VKAPI_CALL debug_utils_messenger_callback(
		VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
		VkDebugUtilsMessageTypeFlagsEXT message_type,
		const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
		void* user_data)
	{
		if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			PHV_CORE_WARN("{0} - {1}: {2}", callback_data->messageIdNumber, callback_data->pMessageIdName, callback_data->pMessage)
		}
		else if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
		{
			PHV_CORE_ERROR("{0} - {1}: {2}", callback_data->messageIdNumber, callback_data->pMessageIdName, callback_data->pMessage);
		}
		else if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
		{
			PHV_CORE_INFO("{0} - {1}: {2}", callback_data->messageIdNumber, callback_data->pMessageIdName, callback_data->pMessage);
		}
		return VK_FALSE;
	}

	VulkanDebug::VulkanDebug(const VkInstance instance)
		: m_instance(instance)
	{
		VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo;
		PopulateDebugUtilsMessengerCreateInfo(debugUtilsMessengerCreateInfo);
		VkResult result = CreateDebugUtilsMessengerEXT(m_instance, &debugUtilsMessengerCreateInfo, nullptr, &m_debugUtilsMessenger);
		PHV_CORE_ASSERT(result != VK_SUCCESS, "Failed to create debug utils messenger!");
	}

	VulkanDebug::~VulkanDebug()
	{
		DestroyDebugUtilsMessengerEXT(m_instance, m_debugUtilsMessenger, nullptr);
	}

	const VkDebugUtilsMessengerEXT VulkanDebug::getDebugUtilsMessengerEXT()
	{
		return m_debugUtilsMessenger;
	}

	void VulkanDebug::PopulateDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugUtilsMessengerInfo)
	{
		debugUtilsMessengerInfo = {};
		debugUtilsMessengerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugUtilsMessengerInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;

		debugUtilsMessengerInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugUtilsMessengerInfo.pfnUserCallback = debug_utils_messenger_callback;
	}

	VkResult VulkanDebug::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void VulkanDebug::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
		if (func != nullptr) {
			func(instance, debugMessenger, pAllocator);
		}
	}

	bool VulkanDebug::IsValidationLayerSupported()
	{
		uint32_t availableLayerCount = 0;
		vkEnumerateInstanceLayerProperties(&availableLayerCount, nullptr);

		eastl::vector<VkLayerProperties> availableLayers(availableLayerCount);
		vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers.data());

		for (const char* layer : validationLayers)
		{
			bool layerFound = false;
			for (const VkLayerProperties& layerProperty : availableLayers)
			{
				if (strcmp(layer, layerProperty.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}
			if (!layerFound)
			{
				return false;
			}
		}
		return true;
	}

}