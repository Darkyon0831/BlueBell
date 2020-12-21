#ifndef __BB_LOGGER_H__
#define __BB_LOGGER_H__

#include "../Core/Core.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#define BB_LOG_INFO(...)  ( ::BlueBell::Logger::GetLogger()->info(__VA_ARGS__) );
#define BB_LOG_WARN(...)  ::BlueBell::Logger::GetLogger()->warn(__VA_ARGS__);
#define BB_LOG_ERR(...)  ::BlueBell::Logger::GetLogger()->error(__VA_ARGS__);
#define BB_LOG_TRACE(...)  ::BlueBell::Logger::GetLogger()->trace(__VA_ARGS__);

#ifdef BB_PLATFORM_WINDOWS
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif 

#define BB_ASSERT(expression, str, ...) if (expression == 0) { char* ___Str___ = ::BlueBell::Logger::GetDebugString(str, __FILENAME__, __func__, __LINE__); ::BlueBell::Logger::GetLogger()->error(___Str___, __VA_ARGS__); ::BlueBell::Logger::DeallocateDebugStr(___Str___); exit(1); };
#define BB_CHECK_HR(hrCode, str, ...) if (hrCode < 0) { char* ___Str___ = ::BlueBell::Logger::GetDebugString(str, __FILENAME__, __func__, __LINE__); ::BlueBell::Logger::GetLogger()->error(___Str___, __VA_ARGS__); ::BlueBell::Logger::DeallocateDebugStr(___Str___); exit(1); };

BB_DISABLE_WARNING_PUSH
BB_DISABLE_WARNING(4251)

namespace BlueBell
{
	class BB_API Logger
	{
	public:

		/**
		* Inits logger
		**/
		static void Init();

		/**
		* Get the core console logger
		**/
		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return m_logger; }

		/**
		* Creates an new file logger 
		*
		* @param filepath: filepath to the file to be writen to
		**/
		static std::shared_ptr<spdlog::logger> CreateNewFileLogger(const char* filepath);

		static char* GetDebugString(const char* str, const char* filed, const char* funcd, int lined);
		static void DeallocateDebugStr(char* debugStr);

	private:
		static std::shared_ptr<spdlog::logger> m_logger;	
	};
}

BB_DISABLE_WARNING_POP

#endif
