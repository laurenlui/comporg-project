# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/citri/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/citri/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/citri/comporg-project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/citri/comporg-project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/comporg-project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/comporg-project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/comporg-project.dir/flags.make

CMakeFiles/comporg-project.dir/p1.cpp.o: CMakeFiles/comporg-project.dir/flags.make
CMakeFiles/comporg-project.dir/p1.cpp.o: ../p1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/citri/comporg-project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/comporg-project.dir/p1.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comporg-project.dir/p1.cpp.o -c /cygdrive/c/Users/citri/comporg-project/p1.cpp

CMakeFiles/comporg-project.dir/p1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comporg-project.dir/p1.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/citri/comporg-project/p1.cpp > CMakeFiles/comporg-project.dir/p1.cpp.i

CMakeFiles/comporg-project.dir/p1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comporg-project.dir/p1.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/citri/comporg-project/p1.cpp -o CMakeFiles/comporg-project.dir/p1.cpp.s

# Object files for target comporg-project
comporg__project_OBJECTS = \
"CMakeFiles/comporg-project.dir/p1.cpp.o"

# External object files for target comporg-project
comporg__project_EXTERNAL_OBJECTS =

comporg-project.exe: CMakeFiles/comporg-project.dir/p1.cpp.o
comporg-project.exe: CMakeFiles/comporg-project.dir/build.make
comporg-project.exe: CMakeFiles/comporg-project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/citri/comporg-project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable comporg-project.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/comporg-project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/comporg-project.dir/build: comporg-project.exe

.PHONY : CMakeFiles/comporg-project.dir/build

CMakeFiles/comporg-project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/comporg-project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/comporg-project.dir/clean

CMakeFiles/comporg-project.dir/depend:
	cd /cygdrive/c/Users/citri/comporg-project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/citri/comporg-project /cygdrive/c/Users/citri/comporg-project /cygdrive/c/Users/citri/comporg-project/cmake-build-debug /cygdrive/c/Users/citri/comporg-project/cmake-build-debug /cygdrive/c/Users/citri/comporg-project/cmake-build-debug/CMakeFiles/comporg-project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/comporg-project.dir/depend

