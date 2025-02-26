#include "VulkanAPI.h"

namespace phv {

	VulkanAPI::VulkanAPI(GLFWwindow* window)
		: m_window(window)
	{
		m_instance = MakeUnique<VulkanInstance>();
		#ifdef PHV_DEBUG
			if (VulkanDebug::IsValidationLayerSupported())
			{
				m_debug = MakeUnique<VulkanDebug>(m_instance->GetInstance());
			}
			else
			{
				PHV_CORE_WARN("VALIDATION LAYERS NOT SUPPORTED! CONTINUING WITHOUT VALIDATION LAYERS!");
			}
		#endif
		m_surface = MakeUnique<VulkanSurface>(m_instance->GetInstance(), m_window);
		m_physicalDevice = MakeUnique<VulkanPhysicalDevice>(m_instance->GetInstance(), m_surface->GetSurface());
		m_logicalDevice = MakeUnique<VulkanLogicalDevice>(m_physicalDevice->GetPhysicalDevice(), m_surface->GetSurface());
	}

}