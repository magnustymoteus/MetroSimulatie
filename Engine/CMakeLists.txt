cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")
set (CMAKE_CXX_STANDARD 17)

############################################################
# List all sources
############################################################
set(engine_sources
	easy_image.cc
	engine.cc engine.h
	ini_configuration.cc l_parser.cc
        ZBuffer.cpp ZBuffer.h Point2D.h Figure.cpp Figure.h Face.cpp Face.h Light.h Light.cpp utils.cpp utils.h Line2D.h Texture.cpp Texture.h obj_parser.h obj_parser.cc)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
set(lib_name "engine_lib")
add_library(${lib_name} ${engine_sources})
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
include_directories(vector)
target_include_directories(engine_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
export(TARGETS engine_lib FILE engineConfig.cmake)
