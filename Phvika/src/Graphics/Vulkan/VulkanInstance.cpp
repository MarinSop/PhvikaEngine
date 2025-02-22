#include "VulkanInstance.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "EASTL/vector.h"
#include <Graphics/Vulkan/VulkanConstants.h>
#include <Graphics/Vulkan/VulkanDebug.h>

namespace phv {

	eastl::vector<const char*> glfwGetRequiredExtensions()
	{
		uint32_t glfwExtensionsCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);
		eastl::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionsCount);
		#ifdef PHV_DEBUG
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		#endif	
		return extensions;
	}

	VulkanInstance::VulkanInstance()
	{
		eastl::vector<const char*> extensions = glfwGetRequiredExtensions();
		VkInstanceCreateInfo instanceInfo{};
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pApplicationInfo = &phv::APP_INFO;
		instanceInfo.ppEnabledExtensionNames = extensions.data();
		instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		#ifdef PHV_DEBUG
			instanceInfo.enabledLayerCount = static_cast<uint32_t>(phv::validationLayers.size());
			instanceInfo.ppEnabledLayerNames = phv::validationLayers.data();
			VkDebugUtilsMessengerCreateInfoEXT debugMessengerInfo;
			VulkanDebug::populateDebugUtilsMessengerCreateInfo(debugMessengerInfo);
			instanceInfo.pNext = static_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&debugMessengerInfo);
		#else
			instanceInfo.enableLayerCount = 0;
			instanceInfo.pNext = nullptr;
		#endif

		VkResult result = vkCreateInstance(&instanceInfo, nullptr, &m_instance);
		PHV_CORE_ASSERT(result != VK_SUCCESS, "Failed to create vulkan instance!");
	}

	VulkanInstance::~VulkanInstance()
	{
		vkDestroyInstance(m_instance, nullptr);
	}

	const VkInstance VulkanInstance::GetInstance()
	{
		return m_instance;
	}

}
