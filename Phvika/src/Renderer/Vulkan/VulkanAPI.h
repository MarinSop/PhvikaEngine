#pragma once
#include "Renderer/RendererAPI.h"
#include "Phvika/Core.h"
#include "Renderer/Vulkan/VulkanInstance.h"

namespace phv {

	class PHV_API VulkanAPI : public RendererAPI
	{
	public:
		virtual void Init();
		virtual void SetViewpoint(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

	private:
		Unique<VulkanInstance> m_instance;
	};

}

