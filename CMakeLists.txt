# CMake version
cmake_minimum_required(VERSION 3.21)

# C++ standard version
set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME Project_L)
set(BUILD_NAME libraries)

# initiating project given its name
project(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES
	include/*.h
	include/*.hpp
	include/*.inl
	src/*.c
	src/*.cpp
)

add_library(${BUILD_NAME} STATIC ${SOURCES})
target_include_directories(${BUILD_NAME} PUBLIC include)

# installing build (using cmake --install command)
install(TARGETS ${BUILD_NAME})
# installing the include files
install(
    DIRECTORY include/
    DESTINATION include
    FILES_MATCHING
    PATTERN *.h
    PATTERN *.hpp
    PATTERN *.inl
)