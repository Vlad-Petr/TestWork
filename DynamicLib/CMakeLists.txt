cmake_minimum_required(VERSION 3.10)
project(DynamicLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
		
set(SOURCE_LIB src/stringsLib.cpp)

add_library(StringsLib SHARED ${SOURCE_LIB})
target_include_directories(StringsLib PUBLIC src)

