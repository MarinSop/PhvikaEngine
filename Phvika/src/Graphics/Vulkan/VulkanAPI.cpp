#include "VulkanAPI.h"

namespace phv {

	VulkanAPI::VulkanAPI(GLFWwindow* window)
		: m_window(window)
	{
		m_instance = MakeUnique<VulkanInstance>();
		#ifdef PHV_DEBUG
			m_debug = MakeUnique<VulkanDebug>(m_instance->GetInstance());
		#endif
		m_surface = MakeUnique<VulkanSurface>(m_instance->GetInstance(), m_window);
	}

}