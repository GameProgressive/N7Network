cmake_minimum_required(VERSION 3.1)
project("N7Network")

option(WITH_MDK "Build MDK with this project")

# Add definitions for w32 build that dosen't support _WIN32 macro
if (WIN32)
	add_definitions("-DWIN32 -D__WIN32__ _D_CRT_SECURE_NO_WARNINGS")
endif()

# Set -fPIC to allow compiling n7network shared library with libuv
if (NOT WIN32)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

# Set CMake output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

## Module Development Kit
if (WITH_MDK)
add_subdirectory("MDK")
include_directories("MDK/include")
endif()

add_subdirectory(common)
add_subdirectory(N7Auth)
