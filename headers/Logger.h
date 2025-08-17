#pragma once

#include <cstdio>
#include <string>
#include <string_view>
#include "Common.h"

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

	inline static void SetLogLevel(LogLevel level) { minLevel = level; }

	inline static void SetOutStream(FILE* stream) { outStream = stream; }

	inline static const char* ToText(LogLevel level) {
		static constexpr const char* levelText[COUNT] = {
			"\033[1;30m[INFO]\033[0m: ",
			"\033[1;36m[DEBUG]\033[0m: ",
			"\033[1;33m[WARN]\033[0m: ",
			"\033[1;31m[ERROR]\033[0m: "};
		return (level >= 0 && level < COUNT) ? levelText[level] : "";
	}

	template <typename... Args> static void Log(const LogLevel lvl, const char* file, const int line, std::string msg, Args... args) {
		Log(lvl, file, line, msg.c_str(), args...);
	}

	template <typename... Args> static void Log(const LogLevel lvl, const char* file, const int line, const char* msg, Args... args) {
		if(lvl < minLevel) return; // Correct filtering
		// Time
		std::fprintf(outStream, "%s", Common::GetFormattedTime());
		// File
		std::fprintf(outStream, "[%s:%d]", file, line);
		// Level
		std::fprintf(outStream, "%s", ToText(lvl));
		// Message (printf-style)
		std::fprintf(outStream, msg, args...);
		std::fputc('\n', outStream);
	}
private:
	inline static LogLevel minLevel  = INFO; // Default to INFO so all are shown unless changed
	inline static FILE*    outStream = stdout;
};