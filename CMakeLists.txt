cmake_minimum_required(VERSION 3.6)
project(INFO0030)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c pnm.c verifications.c verifications.h error.c error.h)
add_executable(INFO0030 ${SOURCE_FILES})