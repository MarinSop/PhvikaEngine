#pragma once

#ifdef PHV_DEBUG
	#ifdef PHV_PLATFORM_WINDOWS
		#define PHV_DEBUG_BREAK() __debugbreak()	
	#endif
#else
		#define PHV_DEBUG_BREAK()	
#endif

#ifdef PHV_ENABLE_ASSERT
	#define PHV_CORE_ASSERT(expr,...)									\
		if (expr)														\
		{																\
			PHV_CORE_CRITICAL("Assertion failed: {0}", __VA_ARGS__);	\
			PHV_DEBUG_BREAK();											\
		}

	#define PHV_ASSERT(expr,...)										\
		if(expr)														\
		{																\
			PHV_CRITICAL("Assertion failed; {0}", __VA_ARGS__);			\
			PHV_DEBUG_BREAK();											\
		}
#else
		#define PHV_CORE_ASSERT(...)
		#define PHV_ASSERT(...)
#endif

#ifdef PHV_PLATFORM_WINDOWS
	#ifdef PHV_BUILD_DLL
		#define PHV_API __declspec(dllexport)
	#else
		#define PHV_API __declspec(dllimport)
	#endif

#endif

#include "Phvika/Log.h"
#include <EASTL/unique_ptr.h>
#include <EASTL/utility.h>
#include <EASTL/memory.h>
#include <EASTL/shared_ptr.h>

namespace phv {

	template<typename T>
	using Unique = eastl::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Unique<T> MakeUnique(Args&& ... args)
	{
		return eastl::make_unique<T>(eastl::forward<Args>(args)...);
	}

	template<typename T>
	using Shared = eastl::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Shared<T> MakeShared(Args&& ... args)
	{
		return eastl::make_shared<T>(eastl::forward<Args>(args)...);
	}
}


