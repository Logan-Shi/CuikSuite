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
include src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/depend.make

# Include the progress variables for this target.
include src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/flags.make

src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.o: src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/flags.make
src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.o: ../src/CuikAtlas/cuikatlas2graph.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikatlas2graph.c

src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikatlas2graph.c > CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.i

src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikatlas2graph.c -o CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.s

# Object files for target cuikatlas2graph
cuikatlas2graph_OBJECTS = \
"CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.o"

# External object files for target cuikatlas2graph
cuikatlas2graph_EXTERNAL_OBJECTS =

../bin/cuikatlas2graph: src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/cuikatlas2graph.o
../bin/cuikatlas2graph: src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/build.make
../bin/cuikatlas2graph: ../lib/libcuikatlas-common.so.3.1.0
../bin/cuikatlas2graph: ../lib/libcuikworld-common.so.3.1.0
../bin/cuikatlas2graph: ../lib/libcuikplot-common.so.3.1.0
../bin/cuikatlas2graph: /usr/lib/libsolid.so
../bin/cuikatlas2graph: ../lib/libcuikvcollide.so.3.1.0
../bin/cuikatlas2graph: /usr/lib/libVCollide.so
../bin/cuikatlas2graph: /usr/lib/libRAPID.so
../bin/cuikatlas2graph: ../lib/libcuikpqp.so.3.1.0
../bin/cuikatlas2graph: /usr/lib/libPQP.so
../bin/cuikatlas2graph: ../lib/libcuikfcl.so.3.1.0
../bin/cuikatlas2graph: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuikatlas2graph: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuikatlas2graph: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuikatlas2graph: ../lib/libcuikbullet.so.3.1.0
../bin/cuikatlas2graph: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuikatlas2graph: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuikatlas2graph: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuikatlas2graph: ../lib/libcuik-common.so.3.1.0
../bin/cuikatlas2graph: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikatlas2graph: /usr/lib/libexpokit.so
../bin/cuikatlas2graph: /usr/local/lib/libglpk.so
../bin/cuikatlas2graph: /usr/local/lib/libgsl.so
../bin/cuikatlas2graph: /usr/lib/libRigidCLL.so
../bin/cuikatlas2graph: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuikatlas2graph: /usr/lib/libcuik-kdtree.so
../bin/cuikatlas2graph: src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuikatlas2graph"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikatlas2graph.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/build: ../bin/cuikatlas2graph

.PHONY : src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/build

src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -P CMakeFiles/cuikatlas2graph.dir/cmake_clean.cmake
.PHONY : src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/clean

src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikAtlas/CMakeFiles/cuikatlas2graph.dir/depend

