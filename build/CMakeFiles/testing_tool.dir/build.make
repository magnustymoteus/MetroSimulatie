# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/magnustymoteus/projects/MetroSimulatie

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/magnustymoteus/projects/MetroSimulatie/build

# Include any dependencies generated for this target.
include CMakeFiles/testing_tool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testing_tool.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testing_tool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testing_tool.dir/flags.make

CMakeFiles/testing_tool.dir/tests/Tests.cpp.o: CMakeFiles/testing_tool.dir/flags.make
CMakeFiles/testing_tool.dir/tests/Tests.cpp.o: ../tests/Tests.cpp
CMakeFiles/testing_tool.dir/tests/Tests.cpp.o: CMakeFiles/testing_tool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/magnustymoteus/projects/MetroSimulatie/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testing_tool.dir/tests/Tests.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testing_tool.dir/tests/Tests.cpp.o -MF CMakeFiles/testing_tool.dir/tests/Tests.cpp.o.d -o CMakeFiles/testing_tool.dir/tests/Tests.cpp.o -c /home/magnustymoteus/projects/MetroSimulatie/tests/Tests.cpp

CMakeFiles/testing_tool.dir/tests/Tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testing_tool.dir/tests/Tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/magnustymoteus/projects/MetroSimulatie/tests/Tests.cpp > CMakeFiles/testing_tool.dir/tests/Tests.cpp.i

CMakeFiles/testing_tool.dir/tests/Tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testing_tool.dir/tests/Tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/magnustymoteus/projects/MetroSimulatie/tests/Tests.cpp -o CMakeFiles/testing_tool.dir/tests/Tests.cpp.s

# Object files for target testing_tool
testing_tool_OBJECTS = \
"CMakeFiles/testing_tool.dir/tests/Tests.cpp.o"

# External object files for target testing_tool
testing_tool_EXTERNAL_OBJECTS =

testing_tool: CMakeFiles/testing_tool.dir/tests/Tests.cpp.o
testing_tool: CMakeFiles/testing_tool.dir/build.make
testing_tool: lib/libgtest.a
testing_tool: CMakeFiles/testing_tool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/magnustymoteus/projects/MetroSimulatie/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testing_tool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testing_tool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testing_tool.dir/build: testing_tool
.PHONY : CMakeFiles/testing_tool.dir/build

CMakeFiles/testing_tool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testing_tool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testing_tool.dir/clean

CMakeFiles/testing_tool.dir/depend:
	cd /home/magnustymoteus/projects/MetroSimulatie/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/magnustymoteus/projects/MetroSimulatie /home/magnustymoteus/projects/MetroSimulatie /home/magnustymoteus/projects/MetroSimulatie/build /home/magnustymoteus/projects/MetroSimulatie/build /home/magnustymoteus/projects/MetroSimulatie/build/CMakeFiles/testing_tool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testing_tool.dir/depend

