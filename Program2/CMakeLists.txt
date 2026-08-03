cmake_minimum_required(VERSION 3.10)
project(Program2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(program2 
    src/main.cpp
    src/SocketClient.cpp
)

set(LIB_SUM_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../lib_sum_project/build")

target_include_directories(program2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../lib_sum_project/src")

target_link_libraries(program2 PRIVATE "${LIB_SUM_PATH}/libstring_sum_lib.so")

set_target_properties(program2 PROPERTIES
    BUILD_RPATH "$ORIGIN:${LIB_SUM_PATH}"
)