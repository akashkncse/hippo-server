cmake_minimum_required(VERSION 3.10)
project(hippo-server)

set(CMAKE_CXX_STANDARD 17)

add_executable(hippo_server
    src/main.cpp
    src/http_parser.cpp
)

target_include_directories(hippo_server PUBLIC src)
