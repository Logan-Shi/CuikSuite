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
CMAKE_SOURCE_DIR = /home/logan/Downloads/CuikSuite3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/logan/Downloads/CuikSuite3/build

# Include any dependencies generated for this target.
include src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/depend.make

# Include the progress variables for this target.
include src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/flags.make

src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.o: src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/flags.make
src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.o: ../src/CuikSimplify/cuikmergeboxes.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.o   -c /home/logan/Downloads/CuikSuite3/src/CuikSimplify/cuikmergeboxes.c

src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikSimplify/cuikmergeboxes.c > CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.i

src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikSimplify/cuikmergeboxes.c -o CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.s

# Object files for target cuikmergeboxes
cuikmergeboxes_OBJECTS = \
"CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.o"

# External object files for target cuikmergeboxes
cuikmergeboxes_EXTERNAL_OBJECTS =

../bin/cuikmergeboxes: src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/cuikmergeboxes.o
../bin/cuikmergeboxes: src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/build.make
../bin/cuikmergeboxes: ../lib/libcuik-common.so.3.1.0
../bin/cuikmergeboxes: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikmergeboxes: /usr/lib/libexpokit.so
../bin/cuikmergeboxes: /usr/local/lib/libglpk.so
../bin/cuikmergeboxes: /usr/local/lib/libgsl.so
../bin/cuikmergeboxes: src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuikmergeboxes"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikmergeboxes.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/build: ../bin/cuikmergeboxes

.PHONY : src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/build

src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify && $(CMAKE_COMMAND) -P CMakeFiles/cuikmergeboxes.dir/cmake_clean.cmake
.PHONY : src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/clean

src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikSimplify /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikSimplify/CMakeFiles/cuikmergeboxes.dir/depend

