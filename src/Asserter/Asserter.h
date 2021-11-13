#pragma once

#include "../Logger/Logger.h"
#include "../Common/Common.h"

#define ASSERTION 1

#if ASSERTION
	#define ASSERT_1_ARGS(expr)																				\
		if (expr) { } 																						\
		else {																								\
			Asserter::Assert(Common::FormatFileName(__FILE__), __LINE__, #expr, "", "");					\
		}
	#define ASSERT_2_ARGS(expr, message)																	\
		if (expr) { } 																						\
		else {																								\
			Asserter::Assert(Common::FormatFileName(__FILE__), __LINE__, #expr, message, "");				\
		}
	#define ASSERT_3_ARGS(expr, message, ...) 																\
		if (expr) { } 																						\
		else {																								\
			Asserter::Assert(Common::FormatFileName(__FILE__), __LINE__, #expr, message, ##__VA_ARGS__);	\
		}

	#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4
	#define ASSERT_MACRO_CHOOSER(...) 					\
				GET_4TH_ARG(__VA_ARGS__, ASSERT_3_ARGS, \
				ASSERT_2_ARGS, ASSERT_1_ARGS, )

	#define ASSERT(...) ASSERT_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
#else
	#define ASSERT(expr, __MSG__)
#endif

namespace Asserter {
	static FILE* outStream = stdout;
	static void SetOutStream(FILE* stream) { outStream = stream; };

	template <typename... Args> static void Assert(const char* file, const int line, const char* expr, const char* msg, Args... args) {
		// Time Vars
		time_t rawtime;
		tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);

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

		// Log
		fprintf(outStream, "[ASSERTION FAILED]: (%s) ", expr);
		fprintf(outStream, msg, args...);
		fprintf(outStream, "\n");
	}
}