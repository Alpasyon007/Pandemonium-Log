#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

#define LOG_DEBUG 1
#define LOG_INFO 1
#define LOG_WARN 1
#define LOG_ERROR 1

#define LOG_INFO(__MSG__, ...)					\
	do {										\
		Logger::Info(__MSG__,  ##__VA_ARGS__);	\
	} while (false)

#define LOG_DEBUG(__MSG__, ...)					\
	do {										\
		Logger::Debug(__MSG__, ##__VA_ARGS__);	\
	} while (false)

#define LOG_WARN(__MSG__, ...)					\
	do {										\
		Logger::Warn(__MSG__,  ##__VA_ARGS__);	\
	} while (false);

#define LOG_ERROR(__MSG__, ...)					\
	do {										\
		Logger::Error(__MSG__,  ##__VA_ARGS__);	\
	} while (false);

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
	static void SetOutStream(FILE* stream) {
		outStream = stream;
	};

	template <typename... Args> static void Info(const char* msg, Args... args) {
		if(logLevel >= INFO) {
				time_t rawtime;
				tm* timeinfo;
				time(&rawtime);
				timeinfo = localtime(&rawtime);

				fprintf(outStream, "[%d:%d:%d]", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
				fprintf(outStream, "[%d %d %d]", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);

				fprintf(outStream, "[INFO]\t");
				fprintf(outStream, msg, args...);
				fprintf(outStream, "\n");
		}
	};

	template <typename... Args> static void Debug(const char* msg, Args... args) {
		if(logLevel >= DEBUG) {
			time_t rawtime;
			tm* timeinfo;
			time(&rawtime);
			timeinfo = localtime(&rawtime);

			fprintf(outStream, "[%d:%d:%d]", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
			fprintf(outStream, "[%d %d %d]", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);

			fprintf(outStream, "[DEBUG]\t");
			fprintf(outStream, msg, args...);
			fprintf(outStream, "\n");
		}
	};

	template <typename... Args> static void Warn(const char* msg, Args... args) {
		if(logLevel >= WARN) {
				time_t rawtime;
				tm* timeinfo;
				time(&rawtime);
				timeinfo = localtime(&rawtime);

				fprintf(outStream, "[%d:%d:%d]", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
				fprintf(outStream, "[%d %d %d]", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);

				fprintf(outStream, "[WARN]\t");
				fprintf(outStream, msg, args...);
				fprintf(outStream, "\n");
		}
	};

	template <typename... Args> static void Error(const char* msg, Args... args) {
		if(logLevel >= ERROR) {
				time_t rawtime;
				tm* timeinfo;
				time(&rawtime);
				timeinfo = localtime(&rawtime);

				fprintf(outStream, "[%d:%d:%d]", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
				fprintf(outStream, "[%d %d %d]", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);

				fprintf(outStream, "[ERROR]\t");
				fprintf(outStream, msg, args...);
				fprintf(outStream, "\n");
		}
	};

}