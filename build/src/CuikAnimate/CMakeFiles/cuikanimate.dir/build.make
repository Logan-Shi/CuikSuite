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
include src/CuikAnimate/CMakeFiles/cuikanimate.dir/depend.make

# Include the progress variables for this target.
include src/CuikAnimate/CMakeFiles/cuikanimate.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikAnimate/CMakeFiles/cuikanimate.dir/flags.make

src/CuikAnimate/CMakeFiles/cuikanimate.dir/cuikanimate.o: src/CuikAnimate/CMakeFiles/cuikanimate.dir/flags.make
src/CuikAnimate/CMakeFiles/cuikanimate.dir/cuikanimate.o: ../src/CuikAnimate/cuikanimate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikAnimate/CMakeFiles/cuikanimate.dir/cuikanimate.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikanimate.dir/cuikanimate.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikanimate.c

src/CuikAnimate/CMakeFiles/cuikanimate.dir/cuikanimate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikanimate.dir/cuikanimate.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikanimate.c > CMakeFiles/cuikanimate.dir/cuikanimate.i

src/CuikAnimate/CMakeFiles/cuikanimate.dir/cuikanimate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikanimate.dir/cuikanimate.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikanimate.c -o CMakeFiles/cuikanimate.dir/cuikanimate.s

# Object files for target cuikanimate
cuikanimate_OBJECTS = \
"CMakeFiles/cuikanimate.dir/cuikanimate.o"

# External object files for target cuikanimate
cuikanimate_EXTERNAL_OBJECTS =

../bin/cuikanimate: src/CuikAnimate/CMakeFiles/cuikanimate.dir/cuikanimate.o
../bin/cuikanimate: src/CuikAnimate/CMakeFiles/cuikanimate.dir/build.make
../bin/cuikanimate: ../lib/libcuikworld-common.so.3.1.0
../bin/cuikanimate: ../lib/libcuikplot-common.so.3.1.0
../bin/cuikanimate: /usr/lib/libsolid.so
../bin/cuikanimate: ../lib/libcuikvcollide.so.3.1.0
../bin/cuikanimate: /usr/lib/libVCollide.so
../bin/cuikanimate: /usr/lib/libRAPID.so
../bin/cuikanimate: ../lib/libcuikpqp.so.3.1.0
../bin/cuikanimate: /usr/lib/libPQP.so
../bin/cuikanimate: ../lib/libcuikfcl.so.3.1.0
../bin/cuikanimate: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuikanimate: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuikanimate: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuikanimate: ../lib/libcuikbullet.so.3.1.0
../bin/cuikanimate: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuikanimate: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuikanimate: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuikanimate: ../lib/libcuik-common.so.3.1.0
../bin/cuikanimate: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikanimate: /usr/lib/libexpokit.so
../bin/cuikanimate: /usr/local/lib/libglpk.so
../bin/cuikanimate: /usr/local/lib/libgsl.so
../bin/cuikanimate: /usr/lib/libRigidCLL.so
../bin/cuikanimate: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuikanimate: src/CuikAnimate/CMakeFiles/cuikanimate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuikanimate"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikanimate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikAnimate/CMakeFiles/cuikanimate.dir/build: ../bin/cuikanimate

.PHONY : src/CuikAnimate/CMakeFiles/cuikanimate.dir/build

src/CuikAnimate/CMakeFiles/cuikanimate.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && $(CMAKE_COMMAND) -P CMakeFiles/cuikanimate.dir/cmake_clean.cmake
.PHONY : src/CuikAnimate/CMakeFiles/cuikanimate.dir/clean

src/CuikAnimate/CMakeFiles/cuikanimate.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikAnimate /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate/CMakeFiles/cuikanimate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikAnimate/CMakeFiles/cuikanimate.dir/depend

