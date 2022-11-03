#pragma once

#include "Logger.h"
#include "Common.h"

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
				ASSERT_2_ARGS, ASSERT_1_ARGS)

	#define ASSERT(...) ASSERT_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)	
#else
	#define ASSERT(expr, __MSG__)
#endif

class Asserter {
public:
	inline static void SetOutStream(FILE* stream) { outStream = stream; };

	template <typename... Args> static void Assert(const char* file, const int line, const char* expr, const char* msg, Args... args) {
		// Time Vars
		fprintf(outStream, "%s", Common::GetFormattedTime());

		// File
		fprintf(outStream, "[%s:%d]", file, line);

		// Log
		fprintf(outStream, "\033[1;31m[ASSERTION FAILED]\033[0m: (%s) ", expr);
		fprintf(outStream, msg, args...);
		fprintf(outStream, "\n");
	}
private:
	inline static FILE* outStream = stdout;
};