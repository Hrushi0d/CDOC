cmake_minimum_required(VERSION 3.16)
project(CDOC LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(CDOC CDOC.cpp)

# Detect GCC version to link stdc++fs if needed (GCC 9 or earlier)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10)
        target_link_libraries(CDOC stdc++fs)
    endif()
endif()
