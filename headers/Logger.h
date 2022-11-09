#pragma once

#include "ppch.h"

#define LOG_INFO_ENABLED  1
#define LOG_DEBUG_ENABLED 1
#define LOG_WARN_ENABLED  1
#define LOG_ERROR_ENABLED 1

#if LOG_INFO_ENABLED
	#define LOG_INFO(__MSG__, ...)                                                                         \
		do {                                                                                               \
			Logger::Log(Logger::INFO, Common::FormatFileName(__FILE__), __LINE__, __MSG__, ##__VA_ARGS__); \
		} while(false);
#else
	#define LOG_INFO(__MSG__, ...)
#endif

#if LOG_DEBUG_ENABLED
	#define LOG_DEBUG(__MSG__, ...)                                                                         \
		do {                                                                                                \
			Logger::Log(Logger::DEBUG, Common::FormatFileName(__FILE__), __LINE__, __MSG__, ##__VA_ARGS__); \
		} while(false);
#else
	#define LOG_DEBUG(__MSG__, ...)
#endif

#if LOG_WARN_ENABLED
	#define LOG_WARN(__MSG__, ...)                                                                         \
		do {                                                                                               \
			Logger::Log(Logger::WARN, Common::FormatFileName(__FILE__), __LINE__, __MSG__, ##__VA_ARGS__); \
		} while(false);
#else
	#define LOG_WARN(__MSG__, ...)
#endif

#if LOG_ERROR_ENABLED
	#define LOG_ERROR(__MSG__, ...)                                                                       \
		do {                                                                                              \
			Logger::Log(Logger::ERR, Common::FormatFileName(__FILE__), __LINE__, __MSG__, ##__VA_ARGS__); \
		} while(false);
#else
	#define LOG_ERROR(__MSG__, ...)
#endif

class Logger {
public:
	enum LogLevel {
		INFO = 0,
		DEBUG,
		WARN,
		ERR,
		COUNT
	};

	inline static void		  SetLogLevel(LogLevel level) { logLevel = level; }

	inline static void		  SetOutStream(FILE* stream) { outStream = stream; }

	inline static const char* ToText(LogLevel level) {
		std::map<LogLevel, const char*> levelStr = {
			{INFO, "\033[1;30m[INFO]\033[0m: "},
			{DEBUG, "\033[1;36m[DEBUG]\033[0m: "},
			{WARN, "\033[1;33m[WARN]\033[0m: "},
			{ERR, "\033[1;31m[ERROR]\033[0m: "},
		};

		for(auto logLevel : levelStr) {
			if(logLevel.first == level) { return logLevel.second; }
		}

		return nullptr;
	}

	template <typename... Args> static void Log(const LogLevel logLevel, const char* file, const int line, std::string msg, Args... args) {
		Log(logLevel, file, line, msg.data(), args...);
	}

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
	}
private:
	inline static LogLevel logLevel	 = ERR;
	inline static FILE*	   outStream = stdout;
};