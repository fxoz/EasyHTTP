cmake_minimum_required(VERSION 3.29)
project(EasyHTTP)

set(CMAKE_CXX_STANDARD 20)
add_executable(EasyHTTP main.cpp
        WebResponse.cpp
        WebResponse.h
        url.cpp
        url.h
        request.cpp
        request.h)
target_link_libraries(EasyHTTP ws2_32)
