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
include src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/depend.make

# Include the progress variables for this target.
include src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/flags.make

src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.o: src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/flags.make
src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.o: ../src/CuikAtlas/cuikrefinetrajectory.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikrefinetrajectory.c

src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikrefinetrajectory.c > CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.i

src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikrefinetrajectory.c -o CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.s

# Object files for target cuikrefinetrajectory
cuikrefinetrajectory_OBJECTS = \
"CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.o"

# External object files for target cuikrefinetrajectory
cuikrefinetrajectory_EXTERNAL_OBJECTS =

../bin/cuikrefinetrajectory: src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/cuikrefinetrajectory.o
../bin/cuikrefinetrajectory: src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/build.make
../bin/cuikrefinetrajectory: ../lib/libcuikatlas-common.so.3.1.0
../bin/cuikrefinetrajectory: ../lib/libcuikworld-common.so.3.1.0
../bin/cuikrefinetrajectory: ../lib/libcuikplot-common.so.3.1.0
../bin/cuikrefinetrajectory: /usr/lib/libsolid.so
../bin/cuikrefinetrajectory: ../lib/libcuikvcollide.so.3.1.0
../bin/cuikrefinetrajectory: /usr/lib/libVCollide.so
../bin/cuikrefinetrajectory: /usr/lib/libRAPID.so
../bin/cuikrefinetrajectory: ../lib/libcuikpqp.so.3.1.0
../bin/cuikrefinetrajectory: /usr/lib/libPQP.so
../bin/cuikrefinetrajectory: ../lib/libcuikfcl.so.3.1.0
../bin/cuikrefinetrajectory: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuikrefinetrajectory: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuikrefinetrajectory: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuikrefinetrajectory: ../lib/libcuikbullet.so.3.1.0
../bin/cuikrefinetrajectory: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuikrefinetrajectory: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuikrefinetrajectory: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuikrefinetrajectory: ../lib/libcuik-common.so.3.1.0
../bin/cuikrefinetrajectory: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikrefinetrajectory: /usr/lib/libexpokit.so
../bin/cuikrefinetrajectory: /usr/local/lib/libglpk.so
../bin/cuikrefinetrajectory: /usr/local/lib/libgsl.so
../bin/cuikrefinetrajectory: /usr/lib/libRigidCLL.so
../bin/cuikrefinetrajectory: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuikrefinetrajectory: /usr/lib/libcuik-kdtree.so
../bin/cuikrefinetrajectory: src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuikrefinetrajectory"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikrefinetrajectory.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/build: ../bin/cuikrefinetrajectory

.PHONY : src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/build

src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -P CMakeFiles/cuikrefinetrajectory.dir/cmake_clean.cmake
.PHONY : src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/clean

src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikAtlas/CMakeFiles/cuikrefinetrajectory.dir/depend

