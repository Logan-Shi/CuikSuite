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
include src/CuikSimplify/CMakeFiles/cuikmerge.dir/depend.make

# Include the progress variables for this target.
include src/CuikSimplify/CMakeFiles/cuikmerge.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikSimplify/CMakeFiles/cuikmerge.dir/flags.make

src/CuikSimplify/CMakeFiles/cuikmerge.dir/cuikmerge.o: src/CuikSimplify/CMakeFiles/cuikmerge.dir/flags.make
src/CuikSimplify/CMakeFiles/cuikmerge.dir/cuikmerge.o: ../src/CuikSimplify/cuikmerge.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikSimplify/CMakeFiles/cuikmerge.dir/cuikmerge.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikmerge.dir/cuikmerge.o   -c /home/logan/Downloads/CuikSuite3/src/CuikSimplify/cuikmerge.c

src/CuikSimplify/CMakeFiles/cuikmerge.dir/cuikmerge.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikmerge.dir/cuikmerge.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikSimplify/cuikmerge.c > CMakeFiles/cuikmerge.dir/cuikmerge.i

src/CuikSimplify/CMakeFiles/cuikmerge.dir/cuikmerge.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikmerge.dir/cuikmerge.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikSimplify/cuikmerge.c -o CMakeFiles/cuikmerge.dir/cuikmerge.s

# Object files for target cuikmerge
cuikmerge_OBJECTS = \
"CMakeFiles/cuikmerge.dir/cuikmerge.o"

# External object files for target cuikmerge
cuikmerge_EXTERNAL_OBJECTS =

../bin/cuikmerge: src/CuikSimplify/CMakeFiles/cuikmerge.dir/cuikmerge.o
../bin/cuikmerge: src/CuikSimplify/CMakeFiles/cuikmerge.dir/build.make
../bin/cuikmerge: ../lib/libcuik-common.so.3.1.0
../bin/cuikmerge: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikmerge: /usr/lib/libexpokit.so
../bin/cuikmerge: /usr/local/lib/libglpk.so
../bin/cuikmerge: /usr/local/lib/libgsl.so
../bin/cuikmerge: src/CuikSimplify/CMakeFiles/cuikmerge.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuikmerge"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikmerge.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikSimplify/CMakeFiles/cuikmerge.dir/build: ../bin/cuikmerge

.PHONY : src/CuikSimplify/CMakeFiles/cuikmerge.dir/build

src/CuikSimplify/CMakeFiles/cuikmerge.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify && $(CMAKE_COMMAND) -P CMakeFiles/cuikmerge.dir/cmake_clean.cmake
.PHONY : src/CuikSimplify/CMakeFiles/cuikmerge.dir/clean

src/CuikSimplify/CMakeFiles/cuikmerge.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikSimplify /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify /home/logan/Downloads/CuikSuite3/build/src/CuikSimplify/CMakeFiles/cuikmerge.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikSimplify/CMakeFiles/cuikmerge.dir/depend
