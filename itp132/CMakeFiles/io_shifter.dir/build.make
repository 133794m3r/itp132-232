# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/macarthur/misc_proj/cplus_programs/itp132

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/macarthur/misc_proj/cplus_programs/itp132

# Include any dependencies generated for this target.
include CMakeFiles/io_shifter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/io_shifter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/io_shifter.dir/flags.make

CMakeFiles/io_shifter.dir/io_shifter.cpp.o: CMakeFiles/io_shifter.dir/flags.make
CMakeFiles/io_shifter.dir/io_shifter.cpp.o: io_shifter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/macarthur/misc_proj/cplus_programs/itp132/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/io_shifter.dir/io_shifter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/io_shifter.dir/io_shifter.cpp.o -c /home/macarthur/misc_proj/cplus_programs/itp132/io_shifter.cpp

CMakeFiles/io_shifter.dir/io_shifter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/io_shifter.dir/io_shifter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/macarthur/misc_proj/cplus_programs/itp132/io_shifter.cpp > CMakeFiles/io_shifter.dir/io_shifter.cpp.i

CMakeFiles/io_shifter.dir/io_shifter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/io_shifter.dir/io_shifter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/macarthur/misc_proj/cplus_programs/itp132/io_shifter.cpp -o CMakeFiles/io_shifter.dir/io_shifter.cpp.s

# Object files for target io_shifter
io_shifter_OBJECTS = \
"CMakeFiles/io_shifter.dir/io_shifter.cpp.o"

# External object files for target io_shifter
io_shifter_EXTERNAL_OBJECTS =

io_shifter: CMakeFiles/io_shifter.dir/io_shifter.cpp.o
io_shifter: CMakeFiles/io_shifter.dir/build.make
io_shifter: CMakeFiles/io_shifter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/macarthur/misc_proj/cplus_programs/itp132/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable io_shifter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/io_shifter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/io_shifter.dir/build: io_shifter

.PHONY : CMakeFiles/io_shifter.dir/build

CMakeFiles/io_shifter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/io_shifter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/io_shifter.dir/clean

CMakeFiles/io_shifter.dir/depend:
	cd /home/macarthur/misc_proj/cplus_programs/itp132 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/macarthur/misc_proj/cplus_programs/itp132 /home/macarthur/misc_proj/cplus_programs/itp132 /home/macarthur/misc_proj/cplus_programs/itp132 /home/macarthur/misc_proj/cplus_programs/itp132 /home/macarthur/misc_proj/cplus_programs/itp132/CMakeFiles/io_shifter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/io_shifter.dir/depend
