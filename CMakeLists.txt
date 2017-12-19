cmake_minimum_required(VERSION 3.2)
project(cpp-mempool VERSION 1.0)

# Do the release build by default
# For debug builds, please use: 'cmake .. -DCMAKE_BUILD_TYPE=Debug'
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Warnings and debug/release modes
set(CMAKE_CXX_FLAGS "-Wall -fdiagnostics-color=always")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the current directory to the include list
include_directories("${PROJECT_SOURCE_DIR}")

add_executable(run_tests test/tests.cpp)
