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
include src/CuikAtlas/CMakeFiles/cuikME.dir/depend.make

# Include the progress variables for this target.
include src/CuikAtlas/CMakeFiles/cuikME.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikAtlas/CMakeFiles/cuikME.dir/flags.make

src/CuikAtlas/CMakeFiles/cuikME.dir/cuikME.o: src/CuikAtlas/CMakeFiles/cuikME.dir/flags.make
src/CuikAtlas/CMakeFiles/cuikME.dir/cuikME.o: ../src/CuikAtlas/cuikME.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikAtlas/CMakeFiles/cuikME.dir/cuikME.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikME.dir/cuikME.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikME.c

src/CuikAtlas/CMakeFiles/cuikME.dir/cuikME.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikME.dir/cuikME.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikME.c > CMakeFiles/cuikME.dir/cuikME.i

src/CuikAtlas/CMakeFiles/cuikME.dir/cuikME.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikME.dir/cuikME.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikME.c -o CMakeFiles/cuikME.dir/cuikME.s

# Object files for target cuikME
cuikME_OBJECTS = \
"CMakeFiles/cuikME.dir/cuikME.o"

# External object files for target cuikME
cuikME_EXTERNAL_OBJECTS =

../bin/cuikME: src/CuikAtlas/CMakeFiles/cuikME.dir/cuikME.o
../bin/cuikME: src/CuikAtlas/CMakeFiles/cuikME.dir/build.make
../bin/cuikME: ../lib/libcuikatlas-common.so.3.1.0
../bin/cuikME: ../lib/libcuikworld-common.so.3.1.0
../bin/cuikME: ../lib/libcuikplot-common.so.3.1.0
../bin/cuikME: /usr/lib/libsolid.so
../bin/cuikME: ../lib/libcuikvcollide.so.3.1.0
../bin/cuikME: /usr/lib/libVCollide.so
../bin/cuikME: /usr/lib/libRAPID.so
../bin/cuikME: ../lib/libcuikpqp.so.3.1.0
../bin/cuikME: /usr/lib/libPQP.so
../bin/cuikME: ../lib/libcuikfcl.so.3.1.0
../bin/cuikME: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuikME: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuikME: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuikME: ../lib/libcuikbullet.so.3.1.0
../bin/cuikME: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuikME: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuikME: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuikME: ../lib/libcuik-common.so.3.1.0
../bin/cuikME: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikME: /usr/lib/libexpokit.so
../bin/cuikME: /usr/local/lib/libglpk.so
../bin/cuikME: /usr/local/lib/libgsl.so
../bin/cuikME: /usr/lib/libRigidCLL.so
../bin/cuikME: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuikME: /usr/lib/libcuik-kdtree.so
../bin/cuikME: src/CuikAtlas/CMakeFiles/cuikME.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuikME"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikME.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikAtlas/CMakeFiles/cuikME.dir/build: ../bin/cuikME

.PHONY : src/CuikAtlas/CMakeFiles/cuikME.dir/build

src/CuikAtlas/CMakeFiles/cuikME.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -P CMakeFiles/cuikME.dir/cmake_clean.cmake
.PHONY : src/CuikAtlas/CMakeFiles/cuikME.dir/clean

src/CuikAtlas/CMakeFiles/cuikME.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas/CMakeFiles/cuikME.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikAtlas/CMakeFiles/cuikME.dir/depend
