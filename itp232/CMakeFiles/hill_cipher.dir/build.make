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
CMAKE_SOURCE_DIR = /home/macarthur/misc_proj/cplus_programs/itp232

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/macarthur/misc_proj/cplus_programs/itp232

# Include any dependencies generated for this target.
include CMakeFiles/hill_cipher.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hill_cipher.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hill_cipher.dir/flags.make

CMakeFiles/hill_cipher.dir/hill_cipher.cpp.o: CMakeFiles/hill_cipher.dir/flags.make
CMakeFiles/hill_cipher.dir/hill_cipher.cpp.o: hill_cipher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/macarthur/misc_proj/cplus_programs/itp232/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hill_cipher.dir/hill_cipher.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hill_cipher.dir/hill_cipher.cpp.o -c /home/macarthur/misc_proj/cplus_programs/itp232/hill_cipher.cpp

CMakeFiles/hill_cipher.dir/hill_cipher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hill_cipher.dir/hill_cipher.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/macarthur/misc_proj/cplus_programs/itp232/hill_cipher.cpp > CMakeFiles/hill_cipher.dir/hill_cipher.cpp.i

CMakeFiles/hill_cipher.dir/hill_cipher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hill_cipher.dir/hill_cipher.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/macarthur/misc_proj/cplus_programs/itp232/hill_cipher.cpp -o CMakeFiles/hill_cipher.dir/hill_cipher.cpp.s

# Object files for target hill_cipher
hill_cipher_OBJECTS = \
"CMakeFiles/hill_cipher.dir/hill_cipher.cpp.o"

# External object files for target hill_cipher
hill_cipher_EXTERNAL_OBJECTS =

hill_cipher: CMakeFiles/hill_cipher.dir/hill_cipher.cpp.o
hill_cipher: CMakeFiles/hill_cipher.dir/build.make
hill_cipher: CMakeFiles/hill_cipher.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/macarthur/misc_proj/cplus_programs/itp232/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hill_cipher"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hill_cipher.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hill_cipher.dir/build: hill_cipher

.PHONY : CMakeFiles/hill_cipher.dir/build

CMakeFiles/hill_cipher.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hill_cipher.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hill_cipher.dir/clean

CMakeFiles/hill_cipher.dir/depend:
	cd /home/macarthur/misc_proj/cplus_programs/itp232 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/macarthur/misc_proj/cplus_programs/itp232 /home/macarthur/misc_proj/cplus_programs/itp232 /home/macarthur/misc_proj/cplus_programs/itp232 /home/macarthur/misc_proj/cplus_programs/itp232 /home/macarthur/misc_proj/cplus_programs/itp232/CMakeFiles/hill_cipher.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hill_cipher.dir/depend
