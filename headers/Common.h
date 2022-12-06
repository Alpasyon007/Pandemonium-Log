#pragma once

#include <chrono>
#include <string>

namespace Common {
	// Remove file path from __FILE__
	static char* FormatFileName(char* file) {
		int count = 0;
		for(int i = 0; i < strlen(file); i++) {
#if defined(PANDEMONIUM_PLATFORM_WINDOWS) // File path seperators are \ instead of / on windows
			if(file[i] == '\\')
#else
			if(file[i] == '/')
#endif /* PANDEMONIUM_PLATFORM_WINDOWS */
			{
				count = i + 1;
			}
		}
		return file += count;
	}

	static char* GetFormattedTime() {
		static char							  buffer[28];

		// Time Vars
		tm									  timeInfo;
		std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
		time_t								  now		  = std::chrono::system_clock::to_time_t(currentTime);
		localtime_s(&timeInfo, &now);

		// Time and File
		sprintf_s(buffer, "[%d/%d/%d][%d:%d:%d.%d]", timeInfo.tm_mday, timeInfo.tm_mon + 1, timeInfo.tm_year + 1900, timeInfo.tm_hour, timeInfo.tm_min,
				  timeInfo.tm_sec, static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count() % 1000));

		return buffer;
	}
} // namespace Common