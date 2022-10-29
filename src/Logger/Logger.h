#pragma once

#include <iostream>
#include <map>

#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_WARN_ENABLED 1
#define LOG_ERROR_ENABLED 1

#if LOG_INFO_ENABLED
	#define LOG_INFO(__MSG__, ...)																			\
		do {																								\
			Logger::Log(Logger::INFO, Common::FormatFileName(__FILE__), __LINE__, __MSG__,  ##__VA_ARGS__);	\
		} while (false)
#else
	#define LOG_INFO(__MSG__, ...)
#endif

#if LOG_DEBUG_ENABLED
	#define LOG_DEBUG(__MSG__, ...)																			\
		do {																								\
			Logger::Log(Logger::DEBUG, Common::FormatFileName(__FILE__), __LINE__, __MSG__, ##__VA_ARGS__);	\
		} while (false)
#else
	#define LOG_DEBUG(__MSG__, ...)
#endif

#if LOG_WARN_ENABLED
	#define LOG_WARN(__MSG__, ...)																			\
		do {																								\
			Logger::Log(Logger::WARN, Common::FormatFileName(__FILE__), __LINE__, __MSG__,  ##__VA_ARGS__);	\
		} while (false);
#else
	#define LOG_WARN(__MSG__, ...)
#endif

#if LOG_ERROR_ENABLED
	#define LOG_ERROR(__MSG__, ...)																			\
		do {																								\
			Logger::Log(Logger::ERROR, Common::FormatFileName(__FILE__), __LINE__, __MSG__, ##__VA_ARGS__);	\
		} while (false);
#else
	#define LOG_ERROR(__MSG__, ...)
#endif

namespace Logger {

	enum LogLevel {
		INFO = 0,
		DEBUG,
		WARN,
		ERROR,
		COUNT
	};

	static LogLevel logLevel = ERROR;
	static FILE* outStream = stdout;

	static void SetLogLevel(LogLevel level) { logLevel = level; };
	static void SetOutStream(FILE* stream) { outStream = stream; };

	static const char* ToText(LogLevel level) {
		std::map<LogLevel, const char*> levelStr = {
			{INFO,		"[INFO]: "},
			{DEBUG,		"[DEBUG]: "},
			{WARN,		"[WARN]: "},
			{ERROR,		"[ERROR]: "},
		};

		for(auto logLevel : levelStr) {
			if(logLevel.first == level) {
				return logLevel.second;
			}
		}

		return nullptr;
	};

	template <typename... Args> static void Log(const LogLevel logLevel, const char* file, const int line, const char* msg, Args... args) {
		if(logLevel >= INFO) {
			// Time
			fprintf(outStream, "%s", Common::GetFormattedTime());

			// File
			fprintf(outStream, "[%s:%d]", file, line);

			// Log Level
			fprintf(outStream, ToText(logLevel));

			// Log
			fprintf(outStream, msg, args...);
			fprintf(outStream, "\n");
		}
	};
}