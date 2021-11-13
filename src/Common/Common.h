#pragma once

#include <cstring>

namespace Common {
	// Remove file path from __FILE__
	static char* FormatFileName(char* file) {
		int count = 0;
		for (int i = 0; i < strlen(file); i++) {
			if(file[i] == '/') { count = i + 1; }
		}
		return file += count;
	}
}