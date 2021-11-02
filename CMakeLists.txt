# CMake Bulid File
#
# CMake Version
cmake_minimum_required(VERSION 3.10)

# Compiler Settings
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set Variables
set(SOURCE_DIR src)

# Set the project name
project(Logger)

# Add the executable
add_executable(
	Logger
	${SOURCE_DIR}/main.cpp
	${SOURCE_DIR}/Asserter/Asserter.h
	${SOURCE_DIR}/Logger/Logger.cpp
	${SOURCE_DIR}/Logger/Logger.h
	)

# Include target directories
target_include_directories(
		Logger
		PRIVATE
		${SOURCE_DIR}/Asserter
		${SOURCE_DIR}/Logger
	)
