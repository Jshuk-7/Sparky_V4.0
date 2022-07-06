#pragma once

#include <format>
#include <iostream>
#include <vector>
#include <string>

#include "Config/Defines.h"

namespace Sparky {
	enum class LogType {
		Trace    = 0,
		Warning  = 1,
		Error    = 2,
		Critical = 3,
	};

	struct LogEntry {
		LogType type;
		const std::string& message;

		LogEntry(LogType type, const std::string& message)
			: type(type), message(message) { }
	};

	class Log
	{
	public:
		static const i8* s_LogBaseMessage;

		static std::string GetCurrentTime();
		static auto GetLogs() { return s_Logs; }
		static void PushEntry(const LogEntry& entry);
	private:
		static std::vector<std::string> s_Logs;
	};
}

using Sparky::Log;
using Sparky::LogType;

#ifdef SP_DEBUG
	#define SP_TRACE(message)    Log::PushEntry({LogType::Trace, message})
	#define SP_WARN(message)     Log::PushEntry({LogType::Warning, message})
	#define SP_ERROR(message)    Log::PushEntry({LogType::Error, message})
	#define SP_FATAL(message)    Log::PushEntry({LogType::Critical, message})
#elif SP_RELEASE
	#define SP_TRACE(message)   
	#define SP_WARN(message)	
	#define SP_ERROR(message)	
	#define SP_FATAL(message)
#endif