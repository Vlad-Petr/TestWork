cmake_minimum_required(VERSION 3.10)
project(Program1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(program1 
    src/main.cpp
    src/Producer.cpp
    src/Consumer.cpp
    src/SocketServer.cpp 
)

find_package(Threads REQUIRED)
target_link_libraries(program1 PRIVATE Threads::Threads)