#include <iostream>
#include <chrono>
#include <ctime>

#include "Log.h"

std::vector<std::string> Sparky::Log::s_Logs;
const Sparky::i8* Sparky::Log::s_LogBaseMessage = "SPARKY: ";

std::string Sparky::Log::GetCurrentTime()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string result(30, '\0');
	std::strftime(&result[0], result.size(), "%A %I:%M", std::localtime(&now));

	return result;
}

void Sparky::Log::PushEntry(const LogEntry& entry)
{
	s_Logs.push_back(entry.message);
}