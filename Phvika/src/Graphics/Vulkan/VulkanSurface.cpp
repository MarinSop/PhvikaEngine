#include "VulkanSurface.h"

phv::VulkanSurface::VulkanSurface(const VkInstance instance, GLFWwindow* window)
    :m_instance(instance), m_window(window)
{
    glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface);
}

phv::VulkanSurface::~VulkanSurface()
{
    vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
}

const VkSurfaceKHR phv::VulkanSurface::GetSurface()
{
    return m_surface;
}
