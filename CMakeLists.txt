cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(RomainOS)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++1z")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/libc/include)

FILE (GLOB_RECURSE kernel_C_SOURCES "*.c")
FILE (GLOB_RECURSE kernel_CPP_SOURCES "*.cpp")

set(EXECUTABLE_NAME "RomainOS")

add_executable(${EXECUTABLE_NAME} ${kernel_C_SOURCES} ${kernel_CPP_SOURCES})
