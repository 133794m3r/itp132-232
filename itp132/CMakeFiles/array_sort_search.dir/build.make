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
include CMakeFiles/array_sort_search.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/array_sort_search.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/array_sort_search.dir/flags.make

CMakeFiles/array_sort_search.dir/array_sort_search.cpp.o: CMakeFiles/array_sort_search.dir/flags.make
CMakeFiles/array_sort_search.dir/array_sort_search.cpp.o: array_sort_search.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/macarthur/misc_proj/cplus_programs/itp132/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/array_sort_search.dir/array_sort_search.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/array_sort_search.dir/array_sort_search.cpp.o -c /home/macarthur/misc_proj/cplus_programs/itp132/array_sort_search.cpp

CMakeFiles/array_sort_search.dir/array_sort_search.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/array_sort_search.dir/array_sort_search.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/macarthur/misc_proj/cplus_programs/itp132/array_sort_search.cpp > CMakeFiles/array_sort_search.dir/array_sort_search.cpp.i

CMakeFiles/array_sort_search.dir/array_sort_search.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/array_sort_search.dir/array_sort_search.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/macarthur/misc_proj/cplus_programs/itp132/array_sort_search.cpp -o CMakeFiles/array_sort_search.dir/array_sort_search.cpp.s

# Object files for target array_sort_search
array_sort_search_OBJECTS = \
"CMakeFiles/array_sort_search.dir/array_sort_search.cpp.o"

# External object files for target array_sort_search
array_sort_search_EXTERNAL_OBJECTS =

array_sort_search: CMakeFiles/array_sort_search.dir/array_sort_search.cpp.o
array_sort_search: CMakeFiles/array_sort_search.dir/build.make
array_sort_search: CMakeFiles/array_sort_search.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/macarthur/misc_proj/cplus_programs/itp132/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable array_sort_search"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/array_sort_search.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/array_sort_search.dir/build: array_sort_search

.PHONY : CMakeFiles/array_sort_search.dir/build

CMakeFiles/array_sort_search.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/array_sort_search.dir/cmake_clean.cmake
.PHONY : CMakeFiles/array_sort_search.dir/clean

CMakeFiles/array_sort_search.dir/depend:
	cd /home/macarthur/misc_proj/cplus_programs/itp132 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/macarthur/misc_proj/cplus_programs/itp132 /home/macarthur/misc_proj/cplus_programs/itp132 /home/macarthur/misc_proj/cplus_programs/itp132 /home/macarthur/misc_proj/cplus_programs/itp132 /home/macarthur/misc_proj/cplus_programs/itp132/CMakeFiles/array_sort_search.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/array_sort_search.dir/depend

