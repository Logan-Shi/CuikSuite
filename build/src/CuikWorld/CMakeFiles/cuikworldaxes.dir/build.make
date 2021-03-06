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
include src/CuikWorld/CMakeFiles/cuikworldaxes.dir/depend.make

# Include the progress variables for this target.
include src/CuikWorld/CMakeFiles/cuikworldaxes.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikWorld/CMakeFiles/cuikworldaxes.dir/flags.make

src/CuikWorld/CMakeFiles/cuikworldaxes.dir/cuikworldaxes.o: src/CuikWorld/CMakeFiles/cuikworldaxes.dir/flags.make
src/CuikWorld/CMakeFiles/cuikworldaxes.dir/cuikworldaxes.o: ../src/CuikWorld/cuikworldaxes.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikWorld/CMakeFiles/cuikworldaxes.dir/cuikworldaxes.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikworldaxes.dir/cuikworldaxes.o   -c /home/logan/Downloads/CuikSuite3/src/CuikWorld/cuikworldaxes.c

src/CuikWorld/CMakeFiles/cuikworldaxes.dir/cuikworldaxes.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikworldaxes.dir/cuikworldaxes.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikWorld/cuikworldaxes.c > CMakeFiles/cuikworldaxes.dir/cuikworldaxes.i

src/CuikWorld/CMakeFiles/cuikworldaxes.dir/cuikworldaxes.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikworldaxes.dir/cuikworldaxes.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikWorld/cuikworldaxes.c -o CMakeFiles/cuikworldaxes.dir/cuikworldaxes.s

# Object files for target cuikworldaxes
cuikworldaxes_OBJECTS = \
"CMakeFiles/cuikworldaxes.dir/cuikworldaxes.o"

# External object files for target cuikworldaxes
cuikworldaxes_EXTERNAL_OBJECTS =

../bin/cuikworldaxes: src/CuikWorld/CMakeFiles/cuikworldaxes.dir/cuikworldaxes.o
../bin/cuikworldaxes: src/CuikWorld/CMakeFiles/cuikworldaxes.dir/build.make
../bin/cuikworldaxes: ../lib/libcuikworld-common.so.3.1.0
../bin/cuikworldaxes: ../lib/libcuikplot-common.so.3.1.0
../bin/cuikworldaxes: /usr/lib/libsolid.so
../bin/cuikworldaxes: ../lib/libcuikvcollide.so.3.1.0
../bin/cuikworldaxes: /usr/lib/libVCollide.so
../bin/cuikworldaxes: /usr/lib/libRAPID.so
../bin/cuikworldaxes: ../lib/libcuikpqp.so.3.1.0
../bin/cuikworldaxes: /usr/lib/libPQP.so
../bin/cuikworldaxes: ../lib/libcuikfcl.so.3.1.0
../bin/cuikworldaxes: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuikworldaxes: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuikworldaxes: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuikworldaxes: ../lib/libcuikbullet.so.3.1.0
../bin/cuikworldaxes: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuikworldaxes: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuikworldaxes: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuikworldaxes: ../lib/libcuik-common.so.3.1.0
../bin/cuikworldaxes: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikworldaxes: /usr/lib/libexpokit.so
../bin/cuikworldaxes: /usr/local/lib/libglpk.so
../bin/cuikworldaxes: /usr/local/lib/libgsl.so
../bin/cuikworldaxes: /usr/lib/libRigidCLL.so
../bin/cuikworldaxes: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuikworldaxes: src/CuikWorld/CMakeFiles/cuikworldaxes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuikworldaxes"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikworldaxes.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikWorld/CMakeFiles/cuikworldaxes.dir/build: ../bin/cuikworldaxes

.PHONY : src/CuikWorld/CMakeFiles/cuikworldaxes.dir/build

src/CuikWorld/CMakeFiles/cuikworldaxes.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && $(CMAKE_COMMAND) -P CMakeFiles/cuikworldaxes.dir/cmake_clean.cmake
.PHONY : src/CuikWorld/CMakeFiles/cuikworldaxes.dir/clean

src/CuikWorld/CMakeFiles/cuikworldaxes.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikWorld /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikWorld /home/logan/Downloads/CuikSuite3/build/src/CuikWorld/CMakeFiles/cuikworldaxes.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikWorld/CMakeFiles/cuikworldaxes.dir/depend

