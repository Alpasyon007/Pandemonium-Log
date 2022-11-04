#pragma once

// Define debug breaks per platform
#if defined(_MSC_VER) // MSVC
	#define DEBUG_BREAK() __debugbreak()
#elif defined(__i386__) || (__x86_64__) // x86
	#define DEBUG_BREAK() __asm__ volatile("int $0x03")
#elif defined(__thumb__)
	#define DEBUG_BREAK() __asm__ volatile(".inst 0xde01")
#elif defined(__arm__) && !defined(__thumb__) // arm
	#define DEBUG_BREAK() __asm__ volatile(".inst 0xe7f001f0")
#elif defined(__aarch64__) && defined(__APPLE__) // darwin
	#define DEBUG_BREAK() __builtin_debugtrap()
#elif defined(__aarch64__)
	#define DEBUG_BREAK() __asm__ volatile(".inst 0xd4200000")
#elif defined(__powerpc__)
	#define DEBUG_BREAK() __asm__ volatile(".4byte 0x7d821008")
#else
	#define DEBUG_BREAK() // Make sure DEBUG_BREAK is always defined
#endif