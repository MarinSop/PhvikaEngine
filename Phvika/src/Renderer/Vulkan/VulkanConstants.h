#pragma once
#include <EASTL/array.h>
#include <vulkan/vulkan.h>

namespace phv {

    const VkApplicationInfo APP_INFO =
    {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "PhvikaEngine",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "PhvikaEngine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_4
    };

	const eastl::array<const char*> validationLayers
	{
		"VK_LAYER_KHRONOS_validation"
	};
}
