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
include src/CuikNewton/CMakeFiles/cuiknewton.dir/depend.make

# Include the progress variables for this target.
include src/CuikNewton/CMakeFiles/cuiknewton.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikNewton/CMakeFiles/cuiknewton.dir/flags.make

src/CuikNewton/CMakeFiles/cuiknewton.dir/cuiknewton.o: src/CuikNewton/CMakeFiles/cuiknewton.dir/flags.make
src/CuikNewton/CMakeFiles/cuiknewton.dir/cuiknewton.o: ../src/CuikNewton/cuiknewton.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikNewton/CMakeFiles/cuiknewton.dir/cuiknewton.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikNewton && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuiknewton.dir/cuiknewton.o   -c /home/logan/Downloads/CuikSuite3/src/CuikNewton/cuiknewton.c

src/CuikNewton/CMakeFiles/cuiknewton.dir/cuiknewton.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuiknewton.dir/cuiknewton.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikNewton && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikNewton/cuiknewton.c > CMakeFiles/cuiknewton.dir/cuiknewton.i

src/CuikNewton/CMakeFiles/cuiknewton.dir/cuiknewton.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuiknewton.dir/cuiknewton.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikNewton && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikNewton/cuiknewton.c -o CMakeFiles/cuiknewton.dir/cuiknewton.s

# Object files for target cuiknewton
cuiknewton_OBJECTS = \
"CMakeFiles/cuiknewton.dir/cuiknewton.o"

# External object files for target cuiknewton
cuiknewton_EXTERNAL_OBJECTS =

../bin/cuiknewton: src/CuikNewton/CMakeFiles/cuiknewton.dir/cuiknewton.o
../bin/cuiknewton: src/CuikNewton/CMakeFiles/cuiknewton.dir/build.make
../bin/cuiknewton: ../lib/libcuik-common.so.3.1.0
../bin/cuiknewton: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuiknewton: /usr/lib/libexpokit.so
../bin/cuiknewton: /usr/local/lib/libglpk.so
../bin/cuiknewton: /usr/local/lib/libgsl.so
../bin/cuiknewton: src/CuikNewton/CMakeFiles/cuiknewton.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuiknewton"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikNewton && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuiknewton.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikNewton/CMakeFiles/cuiknewton.dir/build: ../bin/cuiknewton

.PHONY : src/CuikNewton/CMakeFiles/cuiknewton.dir/build

src/CuikNewton/CMakeFiles/cuiknewton.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikNewton && $(CMAKE_COMMAND) -P CMakeFiles/cuiknewton.dir/cmake_clean.cmake
.PHONY : src/CuikNewton/CMakeFiles/cuiknewton.dir/clean

src/CuikNewton/CMakeFiles/cuiknewton.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikNewton /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikNewton /home/logan/Downloads/CuikSuite3/build/src/CuikNewton/CMakeFiles/cuiknewton.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikNewton/CMakeFiles/cuiknewton.dir/depend

