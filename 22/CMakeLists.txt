# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(myset VERSION 1.0)

# Set compiler
set(CMAKE_C_COMPILER "C:\\msys64\\ucrt64\\bin\\gcc.exe")
set(CMAKE_CXX_COMPILER "C:\\msys64\\ucrt64\\bin\\g++.exe")

# Set linker
set(CMAKE_EXE_LINKER_FLAGS "-L C:\\msys64\\ucrt64\\bin")
set(CMAKE_SHARED_LINKER_FLAGS "-L C:\\msys64\\ucrt64\\bin")
set(CMAKE_MODULE_LINKER_FLAGS "-L C:\\msys64\\ucrt64\\bin")

# Set the C standard to C89
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic -g")

# Get source files
file(GLOB SRCS *.c)

# Add executable target
add_executable(${PROJECT_NAME} ${SRCS})

# Add include directories (headers)
include_directories(${CMAKE_SOURCE_DIR})

# Custom target for clean
add_custom_target(clean-all
        COMMAND ${CMAKE_BUILD_TOOL} clean
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_clean_target.cmake
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
)
