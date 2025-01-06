# CMake version
cmake_minimum_required(VERSION 3.21)

# C++ standard version
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME Utilities)

option(UTILITIES_BUILD_TESTS "build tests" ON)

# initiating project given its name
project(${PROJECT_NAME})



add_subdirectory(fuutilities)

if (UTILITIES_BUILD_AI_UTILS)
    add_subdirectory(dependencies)
endif()

if (UTILITIES_BUILD_TESTS)
    add_subdirectory(test)
endif()
