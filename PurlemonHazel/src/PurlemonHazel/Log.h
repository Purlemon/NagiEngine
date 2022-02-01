#pragma once

#include<memory>

#include"spdlog/spdlog.h"
#include"spdlog/fmt/ostr.h"
#include"Core.h"


namespace PurlemonHazel {

	class PH_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return core_logger_; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger_; }
		
	private:
		static std::shared_ptr<spdlog::logger>core_logger_; 
		static std::shared_ptr<spdlog::logger>client_logger_;
	};

}

// ºËlogºê
#define PH_CORE_TRACE(...)	::PurlemonHazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PH_CORE_INFO(...)	::PurlemonHazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PH_CORE_WARN(...)	::PurlemonHazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PH_CORE_ERROR(...)	::PurlemonHazel::Log::GetCoreLogger()->error(__VA_ARGS__)

// Ó¦ÓÃlogºê
#define PH_TRACE(...)		::PurlemonHazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PH_INFO(...)		::PurlemonHazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define PH_WARN(...)		::PurlemonHazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PH_ERROR(...)		::PurlemonHazel::Log::GetClientLogger()->error(__VA_ARGS__)


