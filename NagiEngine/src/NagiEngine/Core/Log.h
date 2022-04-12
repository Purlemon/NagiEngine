#pragma once

#include<memory>

#include"spdlog/spdlog.h"
#include"spdlog/fmt/ostr.h"
#include"Core.h"


namespace Nagi {

	class NAGI_API Log
	{
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return core_logger_; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return client_logger_; }
		
	private:
		static std::shared_ptr<spdlog::logger>core_logger_; 
		static std::shared_ptr<spdlog::logger>client_logger_;
	};

}

// ºËlogºê
#define NAGI_CORE_TRACE(...)	::Nagi::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NAGI_CORE_INFO(...)	::Nagi::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NAGI_CORE_WARN(...)	::Nagi::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NAGI_CORE_ERROR(...)	::Nagi::Log::GetCoreLogger()->error(__VA_ARGS__)

// Ó¦ÓÃlogºê
#define NAGI_TRACE(...)		::Nagi::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NAGI_INFO(...)		::Nagi::Log::GetClientLogger()->info(__VA_ARGS__)
#define NAGI_WARN(...)		::Nagi::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NAGI_ERROR(...)		::Nagi::Log::GetClientLogger()->error(__VA_ARGS__)


