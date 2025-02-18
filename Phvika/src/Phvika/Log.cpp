#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace phv {

	std::shared_ptr<spdlog::logger> Log::s_engineLogger = nullptr;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger = nullptr;


	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_engineLogger = spdlog::stdout_color_mt("PHVIKA");
		s_engineLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("APP");
		s_clientLogger->set_level(spdlog::level::trace);
	}


}
