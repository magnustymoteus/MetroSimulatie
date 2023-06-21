cmake_minimum_required(VERSION 3.6)
project(MetroSimulatie)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

include(ExternalProject)

ExternalProject_Add(
        engine
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine"
        BINARY_DIR "${CMAKE_BINARY_DIR}/Engine/cmake-build-debug"
        INSTALL_COMMAND ""
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


add_subdirectory(gtest)

include_directories(gtest/googletest/include)

include_directories(gtest/googlemock/include)
include_directories(tools)
include_directories(components)
### TO EDIT
add_compile_definitions(ENGINE_PATH="./cmake-build-debug/Engine/engine")
######################################

FILE(GLOB_RECURSE SOURCES "components/*.cpp")
FILE(GLOB_RECURSE TOOLS "tools/*")
FILE(GLOB_RECURSE TESTS "tests/*.cpp")

set(RELEASE_SOURCE_FILES ${SOURCES} ${TOOLS} main.cpp)
set(DEBUG_SOURCE_FILES ${TESTS} ${SOURCES} ${TOOLS} tests/tests_main.cpp)

add_executable(main_executable ${RELEASE_SOURCE_FILES})
add_executable(testing_tool ${DEBUG_SOURCE_FILES})
target_link_libraries(main_executable PRIVATE Qt5::Widgets)
target_link_libraries(testing_tool gtest)
set(lib_name "metronet_lib")
add_library(${lib_name} ${SOURCES})
install( TARGETS main_executable DESTINATION ${PROJECT_SOURCE_DIR}/ )