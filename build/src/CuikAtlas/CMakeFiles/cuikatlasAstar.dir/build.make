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
include src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/depend.make

# Include the progress variables for this target.
include src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/flags.make

src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.o: src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/flags.make
src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.o: ../src/CuikAtlas/cuikatlasAstar.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikatlasAstar.c

src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikatlasAstar.c > CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.i

src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikatlasAstar.c -o CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.s

# Object files for target cuikatlasAstar
cuikatlasAstar_OBJECTS = \
"CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.o"

# External object files for target cuikatlasAstar
cuikatlasAstar_EXTERNAL_OBJECTS =

../bin/cuikatlasAstar: src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/cuikatlasAstar.o
../bin/cuikatlasAstar: src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/build.make
../bin/cuikatlasAstar: ../lib/libcuikatlas-common.so.3.1.0
../bin/cuikatlasAstar: ../lib/libcuikworld-common.so.3.1.0
../bin/cuikatlasAstar: ../lib/libcuikplot-common.so.3.1.0
../bin/cuikatlasAstar: /usr/lib/libsolid.so
../bin/cuikatlasAstar: ../lib/libcuikvcollide.so.3.1.0
../bin/cuikatlasAstar: /usr/lib/libVCollide.so
../bin/cuikatlasAstar: /usr/lib/libRAPID.so
../bin/cuikatlasAstar: ../lib/libcuikpqp.so.3.1.0
../bin/cuikatlasAstar: /usr/lib/libPQP.so
../bin/cuikatlasAstar: ../lib/libcuikfcl.so.3.1.0
../bin/cuikatlasAstar: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuikatlasAstar: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuikatlasAstar: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuikatlasAstar: ../lib/libcuikbullet.so.3.1.0
../bin/cuikatlasAstar: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuikatlasAstar: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuikatlasAstar: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuikatlasAstar: ../lib/libcuik-common.so.3.1.0
../bin/cuikatlasAstar: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikatlasAstar: /usr/lib/libexpokit.so
../bin/cuikatlasAstar: /usr/local/lib/libglpk.so
../bin/cuikatlasAstar: /usr/local/lib/libgsl.so
../bin/cuikatlasAstar: /usr/lib/libRigidCLL.so
../bin/cuikatlasAstar: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuikatlasAstar: /usr/lib/libcuik-kdtree.so
../bin/cuikatlasAstar: src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuikatlasAstar"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikatlasAstar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/build: ../bin/cuikatlasAstar

.PHONY : src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/build

src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -P CMakeFiles/cuikatlasAstar.dir/cmake_clean.cmake
.PHONY : src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/clean

src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikAtlas/CMakeFiles/cuikatlasAstar.dir/depend
