cmake_minimum_required(VERSION 2.8)
project(StringsLibProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_EXE src/testMain.cpp)		
set(SOURCE_LIB src/stringsLib.cpp)

add_library(StringsLib SHARED ${SOURCE_LIB})
target_include_directories(StringsLib PUBLIC src)

add_executable(testApp ${SOURCE_EXE})
target_link_libraries(testApp PRIVATE StringsLib)

set_target_properties(testApp PROPERTIES
    BUILD_RPATH "$ORIGIN"
)
