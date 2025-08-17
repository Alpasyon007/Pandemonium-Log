#pragma once

#include <chrono>
#include <string>
#include <cstring>
#include <cstdio>

namespace Common {
	// Return base filename (strip directories) from a path (handles both '/' and '\\').
	inline const char* FormatFileName(const char* file) {
		if(!file) return "";
		const char* slash  = strrchr(file, '/');
		const char* back   = strrchr(file, '\\');
		const char* result = nullptr;
		if(slash && back) {
			result = (slash > back) ? slash + 1 : back + 1;
		} else if(slash) {
			result = slash + 1;
		} else if(back) {
			result = back + 1;
		} else {
			result = file;
		}
		return result;
	}

	// Thread-local time buffer for basic thread safety.
	inline const char* GetFormattedTime() {
		thread_local char buffer[32];

		// Current time point
		auto now_tp = std::chrono::system_clock::now();
		time_t raw  = std::chrono::system_clock::to_time_t(now_tp);
		tm timeInfo{};
#if defined(_MSC_VER)
		localtime_s(&timeInfo, &raw);
#else
		localtime_r(&raw, &timeInfo);
#endif
		int millis = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(now_tp.time_since_epoch()).count() % 1000);

		// Zero-padded formatting: [dd/mm/yyyy][HH:MM:SS.mmm]
#if defined(_MSC_VER)
		sprintf_s(buffer, "[%02d/%02d/%04d][%02d:%02d:%02d.%03d]", timeInfo.tm_mday, timeInfo.tm_mon + 1,
				  timeInfo.tm_year + 1900, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec, millis);
#else
		std::snprintf(buffer, sizeof(buffer), "[%02d/%02d/%04d][%02d:%02d/%02d.%03d]", timeInfo.tm_mday, timeInfo.tm_mon + 1,
					  timeInfo.tm_year + 1900, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec, millis);
#endif
		return buffer;
	}
} // namespace Common