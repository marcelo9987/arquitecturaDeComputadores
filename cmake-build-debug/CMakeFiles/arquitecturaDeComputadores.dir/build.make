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
CMAKE_SOURCE_DIR = /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/arquitecturaDeComputadores.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/arquitecturaDeComputadores.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/arquitecturaDeComputadores.dir/flags.make

CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.o: CMakeFiles/arquitecturaDeComputadores.dir/flags.make
CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.o: ../practica1/practica1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.o   -c /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores/practica1/practica1.c

CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores/practica1/practica1.c > CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.i

CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores/practica1/practica1.c -o CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.s

# Object files for target arquitecturaDeComputadores
arquitecturaDeComputadores_OBJECTS = \
"CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.o"

# External object files for target arquitecturaDeComputadores
arquitecturaDeComputadores_EXTERNAL_OBJECTS =

arquitecturaDeComputadores: CMakeFiles/arquitecturaDeComputadores.dir/practica1/practica1.c.o
arquitecturaDeComputadores: CMakeFiles/arquitecturaDeComputadores.dir/build.make
arquitecturaDeComputadores: CMakeFiles/arquitecturaDeComputadores.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable arquitecturaDeComputadores"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arquitecturaDeComputadores.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/arquitecturaDeComputadores.dir/build: arquitecturaDeComputadores

.PHONY : CMakeFiles/arquitecturaDeComputadores.dir/build

CMakeFiles/arquitecturaDeComputadores.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/arquitecturaDeComputadores.dir/cmake_clean.cmake
.PHONY : CMakeFiles/arquitecturaDeComputadores.dir/clean

CMakeFiles/arquitecturaDeComputadores.dir/depend:
	cd /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores/cmake-build-debug /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores/cmake-build-debug /mnt/c/Users/imarc/Documents/GitHub/arquitecturaDeComputadores/cmake-build-debug/CMakeFiles/arquitecturaDeComputadores.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/arquitecturaDeComputadores.dir/depend
