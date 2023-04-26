cmake_minimum_required(VERSION 3.6)
project(project_software_practicum2)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

add_subdirectory(gtest)

#include googletest/include dir
include_directories(gtest/googletest/include)

#include the googlemock/include dir
include_directories(gtest/googlemock/include)
include_directories(tools)
include_directories(components)

FILE(GLOB SOURCES "components/*/*.cpp" "components/*/*/*.cpp" "main.cpp")
FILE(GLOB TOOLS "tools/*" "tools/*/*")
FILE(GLOB TESTS "tests/*/*/*.cpp")

set(RELEASE_SOURCE_FILES ${SOURCES} ${TOOLS})
set(DEBUG_SOURCE_FILES ${TESTS} ${SOURCES} ${TOOLS} tests/tests_main.cpp)

add_executable(main_executable ${RELEASE_SOURCE_FILES})
add_executable(testing_tool ${DEBUG_SOURCE_FILES})
target_link_libraries(testing_tool gtest)
