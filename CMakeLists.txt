cmake_minimum_required(VERSION 3.6)
project(MetroSimulatie)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

add_subdirectory(gtest)
add_subdirectory(Engine)

#include googletest/include dir
include_directories(gtest/googletest/include)

#include the googlemock/include dir
include_directories(gtest/googlemock/include)
include_directories(tools)
include_directories(components)
include_directories(Engine engine)
include_directories(Engine/vector)

FILE(GLOB_RECURSE SOURCES "components/*.cpp" "Engine/*.h" "Engine/vector/vector3d.h")
FILE(GLOB_RECURSE TOOLS "tools/*")
FILE(GLOB_RECURSE TESTS "tests/*.cpp")

set(RELEASE_SOURCE_FILES ${SOURCES} ${TOOLS} main.cpp)
set(DEBUG_SOURCE_FILES ${TESTS} ${SOURCES} ${TOOLS} tests/tests_main.cpp)

add_executable(main_executable ${RELEASE_SOURCE_FILES})
target_link_libraries(main_executable engine_lib)
add_executable(testing_tool ${DEBUG_SOURCE_FILES})
target_link_libraries(testing_tool gtest)
