#include "VulkanInstance.h"
#include <GLFW/glfw3.h>
#include "Phvika/Core.h"
#include <Renderer/Vulkan/VulkanConstants.h>
namespace phv {

	VulkanInstance::VulkanInstance()
	{
		uint32_t requiredGLFWExtensionsCount = 0;
		const char** requiredGLFWExtensions = glfwGetRequiredInstanceExtensions(&requiredGLFWExtensionsCount);

		VkInstanceCreateInfo instanceInfo{};
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pApplicationInfo = &phv::APP_INFO;
		instanceInfo.ppEnabledExtensionNames = requiredGLFWExtensions;
		instanceInfo.enabledExtensionCount = requiredGLFWExtensionsCount;
		instanceInfo.enabledLayerCount = static_cast<uint32_t>(phv::validationLayers.size());
		instanceInfo.ppEnabledLayerNames = phv::validationLayers.data();


		VkResult result = vkCreateInstance(&instanceInfo, nullptr, &m_instance);
		PHV_CORE_ASSERT(result != VK_SUCCESS, "Failed to create vulkan instance!");
	}

	VulkanInstance::~VulkanInstance()
	{
		vkDestroyInstance(m_instance, nullptr);
	}

	VkInstance VulkanInstance::GetInstance()
	{
		return m_instance;
	}

}
