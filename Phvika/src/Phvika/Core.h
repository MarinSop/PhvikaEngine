#pragma once

#ifdef PHV_PLATFORM_WINDOWS
	#ifdef PHV_BUILD_DLL
		#define PHV_API __declspec(dllexport)
	#else
		#define PHV_API __declspec(dllimport)
	#endif

#endif
