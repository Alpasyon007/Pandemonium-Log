# # CMake Bulid File
# #
# # CMake Version
# cmake_minimum_required(VERSION 3.10)

# # Compiler Settings
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_CXX_COMPILER_ID MSVC)

# if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
# 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zc:preprocessor")
# endif()

# # Set Variables
# set(SOURCE_DIR src)

# # Set the project name
# project(PandemoniumLogger)

# # Add the executable
# add_executable(
# 	PandemoniumLogger
# 	${SOURCE_DIR}/main.cpp
# 	${SOURCE_DIR}/Asserter/Asserter.h
# 	${SOURCE_DIR}/Logger/Logger.h
# 	${SOURCE_DIR}/Common/Common.h
# 	${SOURCE_DIR}/Break/Break.h
# )

# # Include target directories
# target_include_directories(
# 	PandemoniumLogger
# 	PRIVATE
# 	${SOURCE_DIR}/Asserter
# 	${SOURCE_DIR}/Logger
# 	${SOURCE_DIR}/Common
# 	${SOURCE_DIR}/Break
# )
set_target_properties(PandemoniumLog PROPERTIES LINKER_LANGUAGE CXX)

target_sources(
	PandemoniumLog
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/Include/PandemoniumLog.h
	${CMAKE_CURRENT_SOURCE_DIR}/headers/Asserter.h
	${CMAKE_CURRENT_SOURCE_DIR}/headers/Logger.h
	${CMAKE_CURRENT_SOURCE_DIR}/headers/Common.h
	${CMAKE_CURRENT_SOURCE_DIR}/headers/Break.h
)

target_include_directories(
	PandemoniumLog 
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# target_compile_definitions(myLib PUBLIC)