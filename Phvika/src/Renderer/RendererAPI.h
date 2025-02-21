#pragma once

#include <stdint.h>
#include "Phvika/Core.h"
namespace phv{

class PHV_API RendererAPI
{
public:
	enum class API
	{
		None = 0,
		Vulkan
	};

	virtual ~RendererAPI() = default;

	virtual void Init() = 0;
	virtual void SetViewpoint(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
private:
	static API s_API;
};

}
