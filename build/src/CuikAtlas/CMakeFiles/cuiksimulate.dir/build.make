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
include src/CuikAtlas/CMakeFiles/cuiksimulate.dir/depend.make

# Include the progress variables for this target.
include src/CuikAtlas/CMakeFiles/cuiksimulate.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikAtlas/CMakeFiles/cuiksimulate.dir/flags.make

src/CuikAtlas/CMakeFiles/cuiksimulate.dir/cuiksimulate.o: src/CuikAtlas/CMakeFiles/cuiksimulate.dir/flags.make
src/CuikAtlas/CMakeFiles/cuiksimulate.dir/cuiksimulate.o: ../src/CuikAtlas/cuiksimulate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikAtlas/CMakeFiles/cuiksimulate.dir/cuiksimulate.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuiksimulate.dir/cuiksimulate.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuiksimulate.c

src/CuikAtlas/CMakeFiles/cuiksimulate.dir/cuiksimulate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuiksimulate.dir/cuiksimulate.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuiksimulate.c > CMakeFiles/cuiksimulate.dir/cuiksimulate.i

src/CuikAtlas/CMakeFiles/cuiksimulate.dir/cuiksimulate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuiksimulate.dir/cuiksimulate.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuiksimulate.c -o CMakeFiles/cuiksimulate.dir/cuiksimulate.s

# Object files for target cuiksimulate
cuiksimulate_OBJECTS = \
"CMakeFiles/cuiksimulate.dir/cuiksimulate.o"

# External object files for target cuiksimulate
cuiksimulate_EXTERNAL_OBJECTS =

../bin/cuiksimulate: src/CuikAtlas/CMakeFiles/cuiksimulate.dir/cuiksimulate.o
../bin/cuiksimulate: src/CuikAtlas/CMakeFiles/cuiksimulate.dir/build.make
../bin/cuiksimulate: ../lib/libcuikatlas-common.so.3.1.0
../bin/cuiksimulate: ../lib/libcuikworld-common.so.3.1.0
../bin/cuiksimulate: ../lib/libcuikplot-common.so.3.1.0
../bin/cuiksimulate: /usr/lib/libsolid.so
../bin/cuiksimulate: ../lib/libcuikvcollide.so.3.1.0
../bin/cuiksimulate: /usr/lib/libVCollide.so
../bin/cuiksimulate: /usr/lib/libRAPID.so
../bin/cuiksimulate: ../lib/libcuikpqp.so.3.1.0
../bin/cuiksimulate: /usr/lib/libPQP.so
../bin/cuiksimulate: ../lib/libcuikfcl.so.3.1.0
../bin/cuiksimulate: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuiksimulate: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuiksimulate: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuiksimulate: ../lib/libcuikbullet.so.3.1.0
../bin/cuiksimulate: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuiksimulate: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuiksimulate: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuiksimulate: ../lib/libcuik-common.so.3.1.0
../bin/cuiksimulate: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuiksimulate: /usr/lib/libexpokit.so
../bin/cuiksimulate: /usr/local/lib/libglpk.so
../bin/cuiksimulate: /usr/local/lib/libgsl.so
../bin/cuiksimulate: /usr/lib/libRigidCLL.so
../bin/cuiksimulate: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuiksimulate: /usr/lib/libcuik-kdtree.so
../bin/cuiksimulate: src/CuikAtlas/CMakeFiles/cuiksimulate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuiksimulate"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuiksimulate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikAtlas/CMakeFiles/cuiksimulate.dir/build: ../bin/cuiksimulate

.PHONY : src/CuikAtlas/CMakeFiles/cuiksimulate.dir/build

src/CuikAtlas/CMakeFiles/cuiksimulate.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -P CMakeFiles/cuiksimulate.dir/cmake_clean.cmake
.PHONY : src/CuikAtlas/CMakeFiles/cuiksimulate.dir/clean

src/CuikAtlas/CMakeFiles/cuiksimulate.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas/CMakeFiles/cuiksimulate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikAtlas/CMakeFiles/cuiksimulate.dir/depend

