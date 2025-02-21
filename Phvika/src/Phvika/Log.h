#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <EASTL/memory.h>

namespace phv {

	class PHV_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_engineLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; };

	private:
		static std::shared_ptr<spdlog::logger> s_engineLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};

#define PHV_CORE_ERROR(...) ::phv::Log::GetEngineLogger()->error(__VA_ARGS__);
#define PHJV_CORE_TRACE(...) ::phv::Log::GetEngineLogger()->trace(__VA_ARGS__);
#define PHV_CORE_INFO(...) ::phv::Log::GetEngineLogger()->info(__VA_ARGS__);
#define PHV_CORE_WARN(...) ::phv::Log::GetEngineLogger()->warn(__VA_ARGS__);
#define PHV_CORE_CRITICAL(...) ::phv::Log::GetEngineLogger()->critical(__VA_ARGS__);

#define PHV_ERROR(...) ::phv::Log::GetClientLogger()->error(__VA_ARGS__);
#define PHV_TRACE(...) ::phv::Log::GetClientLogger()->trace(__VA_ARGS__);
#define PHV_INFO(...) ::phv::Log::GetClientLogger()->info(__VA_ARGS__);
#define PHV_WARN(...) ::phv::Log::GetClientLogger()->warn(__VA_ARGS__);
#define PHV_CRITICAL(...) ::phv::Log::GetClientLogger()->critical(__VA_ARGS__);

}

