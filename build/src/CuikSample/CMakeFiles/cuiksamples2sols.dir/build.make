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
include src/CuikSample/CMakeFiles/cuiksamples2sols.dir/depend.make

# Include the progress variables for this target.
include src/CuikSample/CMakeFiles/cuiksamples2sols.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikSample/CMakeFiles/cuiksamples2sols.dir/flags.make

src/CuikSample/CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.o: src/CuikSample/CMakeFiles/cuiksamples2sols.dir/flags.make
src/CuikSample/CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.o: ../src/CuikSample/cuiksamples2sols.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikSample/CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSample && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.o   -c /home/logan/Downloads/CuikSuite3/src/CuikSample/cuiksamples2sols.c

src/CuikSample/CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSample && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikSample/cuiksamples2sols.c > CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.i

src/CuikSample/CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSample && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikSample/cuiksamples2sols.c -o CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.s

# Object files for target cuiksamples2sols
cuiksamples2sols_OBJECTS = \
"CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.o"

# External object files for target cuiksamples2sols
cuiksamples2sols_EXTERNAL_OBJECTS =

../bin/cuiksamples2sols: src/CuikSample/CMakeFiles/cuiksamples2sols.dir/cuiksamples2sols.o
../bin/cuiksamples2sols: src/CuikSample/CMakeFiles/cuiksamples2sols.dir/build.make
../bin/cuiksamples2sols: ../lib/libcuikatlas-common.so.3.1.0
../bin/cuiksamples2sols: ../lib/libcuikworld-common.so.3.1.0
../bin/cuiksamples2sols: ../lib/libcuikplot-common.so.3.1.0
../bin/cuiksamples2sols: /usr/lib/libsolid.so
../bin/cuiksamples2sols: ../lib/libcuikvcollide.so.3.1.0
../bin/cuiksamples2sols: /usr/lib/libVCollide.so
../bin/cuiksamples2sols: /usr/lib/libRAPID.so
../bin/cuiksamples2sols: ../lib/libcuikpqp.so.3.1.0
../bin/cuiksamples2sols: /usr/lib/libPQP.so
../bin/cuiksamples2sols: ../lib/libcuikfcl.so.3.1.0
../bin/cuiksamples2sols: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuiksamples2sols: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuiksamples2sols: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuiksamples2sols: ../lib/libcuikbullet.so.3.1.0
../bin/cuiksamples2sols: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuiksamples2sols: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuiksamples2sols: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuiksamples2sols: ../lib/libcuik-common.so.3.1.0
../bin/cuiksamples2sols: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuiksamples2sols: /usr/lib/libexpokit.so
../bin/cuiksamples2sols: /usr/local/lib/libglpk.so
../bin/cuiksamples2sols: /usr/local/lib/libgsl.so
../bin/cuiksamples2sols: /usr/lib/libRigidCLL.so
../bin/cuiksamples2sols: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuiksamples2sols: /usr/lib/libcuik-kdtree.so
../bin/cuiksamples2sols: src/CuikSample/CMakeFiles/cuiksamples2sols.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuiksamples2sols"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSample && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuiksamples2sols.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikSample/CMakeFiles/cuiksamples2sols.dir/build: ../bin/cuiksamples2sols

.PHONY : src/CuikSample/CMakeFiles/cuiksamples2sols.dir/build

src/CuikSample/CMakeFiles/cuiksamples2sols.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSample && $(CMAKE_COMMAND) -P CMakeFiles/cuiksamples2sols.dir/cmake_clean.cmake
.PHONY : src/CuikSample/CMakeFiles/cuiksamples2sols.dir/clean

src/CuikSample/CMakeFiles/cuiksamples2sols.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikSample /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikSample /home/logan/Downloads/CuikSuite3/build/src/CuikSample/CMakeFiles/cuiksamples2sols.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikSample/CMakeFiles/cuiksamples2sols.dir/depend

