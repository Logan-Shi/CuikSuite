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
include src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/depend.make

# Include the progress variables for this target.
include src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/flags.make

src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.o: src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/flags.make
src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.o: ../src/CuikAtlas/cuikatlasGBF.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikatlasGBF.c

src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikatlasGBF.c > CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.i

src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAtlas/cuikatlasGBF.c -o CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.s

# Object files for target cuikatlasGBF
cuikatlasGBF_OBJECTS = \
"CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.o"

# External object files for target cuikatlasGBF
cuikatlasGBF_EXTERNAL_OBJECTS =

../bin/cuikatlasGBF: src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/cuikatlasGBF.o
../bin/cuikatlasGBF: src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/build.make
../bin/cuikatlasGBF: ../lib/libcuikatlas-common.so.3.1.0
../bin/cuikatlasGBF: ../lib/libcuikworld-common.so.3.1.0
../bin/cuikatlasGBF: ../lib/libcuikplot-common.so.3.1.0
../bin/cuikatlasGBF: /usr/lib/libsolid.so
../bin/cuikatlasGBF: ../lib/libcuikvcollide.so.3.1.0
../bin/cuikatlasGBF: /usr/lib/libVCollide.so
../bin/cuikatlasGBF: /usr/lib/libRAPID.so
../bin/cuikatlasGBF: ../lib/libcuikpqp.so.3.1.0
../bin/cuikatlasGBF: /usr/lib/libPQP.so
../bin/cuikatlasGBF: ../lib/libcuikfcl.so.3.1.0
../bin/cuikatlasGBF: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuikatlasGBF: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuikatlasGBF: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuikatlasGBF: ../lib/libcuikbullet.so.3.1.0
../bin/cuikatlasGBF: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuikatlasGBF: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuikatlasGBF: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuikatlasGBF: ../lib/libcuik-common.so.3.1.0
../bin/cuikatlasGBF: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikatlasGBF: /usr/lib/libexpokit.so
../bin/cuikatlasGBF: /usr/local/lib/libglpk.so
../bin/cuikatlasGBF: /usr/local/lib/libgsl.so
../bin/cuikatlasGBF: /usr/lib/libRigidCLL.so
../bin/cuikatlasGBF: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuikatlasGBF: /usr/lib/libcuik-kdtree.so
../bin/cuikatlasGBF: src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuikatlasGBF"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikatlasGBF.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/build: ../bin/cuikatlasGBF

.PHONY : src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/build

src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas && $(CMAKE_COMMAND) -P CMakeFiles/cuikatlasGBF.dir/cmake_clean.cmake
.PHONY : src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/clean

src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas /home/logan/Downloads/CuikSuite3/build/src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikAtlas/CMakeFiles/cuikatlasGBF.dir/depend

