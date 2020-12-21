#include "Logger.h"
#include "../Core/BlueBerry.h"

#include <sstream>

namespace BlueBell
{
	std::shared_ptr<spdlog::logger> Logger::m_logger;

	void Logger::Init()
	{
		m_logger = spdlog::stdout_color_mt("Logger");
	}

	std::shared_ptr<spdlog::logger> Logger::CreateNewFileLogger(const char* filepath)
	{
		return spdlog::basic_logger_mt(filepath, filepath);
	}

	char* Logger::GetDebugString(const char* str, const char* filed, const char* funcd, int lined)
	{
		std::string lineStr = std::to_string(lined);

		const size_t strSize = strlen(str);
		const size_t fileSize = strlen(filed);
		const size_t funcSize = strlen(funcd);
		const size_t lineSize = lineStr.size();

		char* finalStr = BlueBell::BlueBerry()->AllocateArray<char>(strSize + fileSize + funcSize + lineSize + 4);
		int currentIndex = 0;

		//[file] [func] [line] str

		char startBracket = '[';
		char endBracket = ']';
		char space = ' ';
		char null = '\0';

		memcpy(&finalStr[currentIndex], &startBracket, 1);
		currentIndex += 1;

		memcpy(&finalStr[currentIndex], &filed[0], fileSize);
		currentIndex += fileSize;

		memcpy(&finalStr[currentIndex], &endBracket, 1);
		currentIndex += 1;

		memcpy(&finalStr[currentIndex], &space, 1);
		currentIndex += 1;

		memcpy(&finalStr[currentIndex], &startBracket, 1);
		currentIndex += 1;

		memcpy(&finalStr[currentIndex], &funcd[0], funcSize);
		currentIndex += funcSize;

		memcpy(&finalStr[currentIndex], &endBracket, 1);
		currentIndex += 1;

		memcpy(&finalStr[currentIndex], &space, 1);
		currentIndex += 1;

		memcpy(&finalStr[currentIndex], &startBracket, 1);
		currentIndex += 1;

		memcpy(&finalStr[currentIndex], lineStr.c_str(), lineSize);
		currentIndex += lineSize;

		memcpy(&finalStr[currentIndex], &endBracket, 1);
		currentIndex += 1;

		memcpy(&finalStr[currentIndex], &space, 1);
		currentIndex += 1;

		memcpy(&finalStr[currentIndex], &str[0], strSize);
		currentIndex += strSize;

		memcpy(&finalStr[currentIndex], &null, 1);

		return finalStr;
	}

	void Logger::DeallocateDebugStr(char* debugStr)
	{
		BlueBerry()->Deallocate(debugStr);
	}
}
