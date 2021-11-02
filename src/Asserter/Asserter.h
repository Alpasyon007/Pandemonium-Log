#pragma once

#include "../Logger/Logger.h"

#define ASSERTION 1

#if ASSERTION
	#define ASSERT(expr, __MSG__)										\
		if (expr) { } 													\
		else {															\
			Asserter::Assert(__FILE__, __LINE__, #expr, __MSG__);		\
		}
#else
	#define ASSERT(expr, __MSG__)
#endif

namespace Asserter {

	static FILE* outStream = stdout;
	static void SetOutStream(FILE* stream) { outStream = stream; };

	template <typename... Args> static void Assert(const char* file, const int line, const char* expr, const char* msg) {
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
				fprintf(outStream, "[ASSERTION FAILED]: (%s) %s", expr, msg);
				fprintf(outStream, "\n");
	}

}