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
CMAKE_SOURCE_DIR = /home/reconerboy/local_git/APRobot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/reconerboy/local_git/APRobot/build

# Include any dependencies generated for this target.
include CMakeFiles/MyExecutable.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyExecutable.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyExecutable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyExecutable.dir/flags.make

CMakeFiles/MyExecutable.dir/src/main.cpp.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/MyExecutable.dir/src/main.cpp.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reconerboy/local_git/APRobot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyExecutable.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/src/main.cpp.o -MF CMakeFiles/MyExecutable.dir/src/main.cpp.o.d -o CMakeFiles/MyExecutable.dir/src/main.cpp.o -c /home/reconerboy/local_git/APRobot/src/main.cpp

CMakeFiles/MyExecutable.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyExecutable.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/reconerboy/local_git/APRobot/src/main.cpp > CMakeFiles/MyExecutable.dir/src/main.cpp.i

CMakeFiles/MyExecutable.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyExecutable.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/reconerboy/local_git/APRobot/src/main.cpp -o CMakeFiles/MyExecutable.dir/src/main.cpp.s

# Object files for target MyExecutable
MyExecutable_OBJECTS = \
"CMakeFiles/MyExecutable.dir/src/main.cpp.o"

# External object files for target MyExecutable
MyExecutable_EXTERNAL_OBJECTS =

MyExecutable: CMakeFiles/MyExecutable.dir/src/main.cpp.o
MyExecutable: CMakeFiles/MyExecutable.dir/build.make
MyExecutable: CMakeFiles/MyExecutable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/reconerboy/local_git/APRobot/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MyExecutable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyExecutable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyExecutable.dir/build: MyExecutable
.PHONY : CMakeFiles/MyExecutable.dir/build

CMakeFiles/MyExecutable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyExecutable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyExecutable.dir/clean

CMakeFiles/MyExecutable.dir/depend:
	cd /home/reconerboy/local_git/APRobot/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/reconerboy/local_git/APRobot /home/reconerboy/local_git/APRobot /home/reconerboy/local_git/APRobot/build /home/reconerboy/local_git/APRobot/build /home/reconerboy/local_git/APRobot/build/CMakeFiles/MyExecutable.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyExecutable.dir/depend

