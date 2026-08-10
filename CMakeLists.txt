cmake_minimum_required(VERSION 3.10)
project(drp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/scanner.cpp
    src/reporter.cpp
)

add_executable(drp ${SOURCES})
