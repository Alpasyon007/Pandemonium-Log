#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

#define LOG_INFO 1
#define LOG_DEBUG 1
#define LOG_WARN 1
#define LOG_ERROR 1

#if LOG_INFO
	#define LOG_INFO(__MSG__, ...)													\
		do {																		\
			Logger::Log(Logger::INFO, __FILE__, __LINE__, __MSG__,  ##__VA_ARGS__);	\
		} while (false)
#else
	#define LOG_INFO(__MSG__, ...)
#endif

#if LOG_DEBUG
	#define LOG_DEBUG(__MSG__, ...)													\
		do {																		\
			Logger::Log(Logger::DEBUG, __FILE__, __LINE__, __MSG__, ##__VA_ARGS__);	\
		} while (false)
#else
	#define LOG_DEBUG(__MSG__, ...)
#endif

#if LOG_WARN
	#define LOG_WARN(__MSG__, ...)													\
		do {																		\
			Logger::Log(Logger::WARN, __FILE__, __LINE__, __MSG__,  ##__VA_ARGS__);	\
		} while (false);
#else
	#define LOG_WARN(__MSG__, ...)
#endif

#if LOG_ERROR
	#define LOG_ERROR(__MSG__, ...)													\
		do {																		\
			Logger::Log(Logger::ERROR, __FILE__, __LINE__, __MSG__, ##__VA_ARGS__);	\
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
	};

	static LogLevel logLevel = ERROR;
	static FILE* outStream = stdout;

	static void SetLogLevel(LogLevel level) { logLevel = level; };
	static void SetOutStream(FILE* stream) { outStream = stream; };
	static const char* GetLogLevel(LogLevel level) {
		switch (level) {
		case INFO:
			return "[INFO]: \t";
			break;
		case DEBUG:
			return "[DEBUG]:\t";
			break;
		case WARN:
			return "[WARN]: \t";
			break;
		case ERROR:
			return "[ERROR]:\t";
			break;
		default:
			break;
		}
	};

	template <typename... Args> static void Log(const LogLevel logLevel, const char* file, const int line, const char* msg, Args... args) {
		if(logLevel >= INFO) {
				// Time Vars
				time_t rawtime;
				tm* timeinfo;
				time(&rawtime);
				timeinfo = localtime(&rawtime);

				// Count Vars
				int count = 0;
				int temp = line;

				// Count
				do {
					temp /= 10;
					++count;
				} while (temp != 0);

				// Time and File
				fprintf(outStream, "[%d %d %d %d:%d:%d][%s:%d]",
									timeinfo->tm_mday,
									timeinfo->tm_mon + 1,
									timeinfo->tm_year + 1900,
									timeinfo->tm_hour,
									timeinfo->tm_min,
									timeinfo->tm_sec,
									file,
									line);

				// Alignment spaces
				for (int i = 0; i < 4 - count; i++)
				{
					fprintf(outStream, " ");
					/* code */
				}

				// Log Level
				fprintf(outStream, GetLogLevel(logLevel));

				// Log
				fprintf(outStream, msg, args...);
				fprintf(outStream, "\n");
		}
	};
}