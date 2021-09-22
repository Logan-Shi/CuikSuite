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
include src/CuikAnimate/CMakeFiles/cuiktransform.dir/depend.make

# Include the progress variables for this target.
include src/CuikAnimate/CMakeFiles/cuiktransform.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikAnimate/CMakeFiles/cuiktransform.dir/flags.make

src/CuikAnimate/CMakeFiles/cuiktransform.dir/cuiktransform.o: src/CuikAnimate/CMakeFiles/cuiktransform.dir/flags.make
src/CuikAnimate/CMakeFiles/cuiktransform.dir/cuiktransform.o: ../src/CuikAnimate/cuiktransform.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikAnimate/CMakeFiles/cuiktransform.dir/cuiktransform.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuiktransform.dir/cuiktransform.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuiktransform.c

src/CuikAnimate/CMakeFiles/cuiktransform.dir/cuiktransform.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuiktransform.dir/cuiktransform.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuiktransform.c > CMakeFiles/cuiktransform.dir/cuiktransform.i

src/CuikAnimate/CMakeFiles/cuiktransform.dir/cuiktransform.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuiktransform.dir/cuiktransform.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuiktransform.c -o CMakeFiles/cuiktransform.dir/cuiktransform.s

# Object files for target cuiktransform
cuiktransform_OBJECTS = \
"CMakeFiles/cuiktransform.dir/cuiktransform.o"

# External object files for target cuiktransform
cuiktransform_EXTERNAL_OBJECTS =

../bin/cuiktransform: src/CuikAnimate/CMakeFiles/cuiktransform.dir/cuiktransform.o
../bin/cuiktransform: src/CuikAnimate/CMakeFiles/cuiktransform.dir/build.make
../bin/cuiktransform: ../lib/libcuikworld-common.so.3.1.0
../bin/cuiktransform: ../lib/libcuikplot-common.so.3.1.0
../bin/cuiktransform: /usr/lib/libsolid.so
../bin/cuiktransform: ../lib/libcuikvcollide.so.3.1.0
../bin/cuiktransform: /usr/lib/libVCollide.so
../bin/cuiktransform: /usr/lib/libRAPID.so
../bin/cuiktransform: ../lib/libcuikpqp.so.3.1.0
../bin/cuiktransform: /usr/lib/libPQP.so
../bin/cuiktransform: ../lib/libcuikfcl.so.3.1.0
../bin/cuiktransform: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuiktransform: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuiktransform: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuiktransform: ../lib/libcuikbullet.so.3.1.0
../bin/cuiktransform: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuiktransform: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuiktransform: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuiktransform: ../lib/libcuik-common.so.3.1.0
../bin/cuiktransform: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuiktransform: /usr/lib/libexpokit.so
../bin/cuiktransform: /usr/local/lib/libglpk.so
../bin/cuiktransform: /usr/local/lib/libgsl.so
../bin/cuiktransform: /usr/lib/libRigidCLL.so
../bin/cuiktransform: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuiktransform: src/CuikAnimate/CMakeFiles/cuiktransform.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuiktransform"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuiktransform.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikAnimate/CMakeFiles/cuiktransform.dir/build: ../bin/cuiktransform

.PHONY : src/CuikAnimate/CMakeFiles/cuiktransform.dir/build

src/CuikAnimate/CMakeFiles/cuiktransform.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && $(CMAKE_COMMAND) -P CMakeFiles/cuiktransform.dir/cmake_clean.cmake
.PHONY : src/CuikAnimate/CMakeFiles/cuiktransform.dir/clean

src/CuikAnimate/CMakeFiles/cuiktransform.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikAnimate /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate/CMakeFiles/cuiktransform.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikAnimate/CMakeFiles/cuiktransform.dir/depend

