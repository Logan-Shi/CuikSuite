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
include src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/depend.make

# Include the progress variables for this target.
include src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/flags.make

src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.o: src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/flags.make
src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.o: ../src/CuikSingular/cuikaddjacobian.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSingular && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.o   -c /home/logan/Downloads/CuikSuite3/src/CuikSingular/cuikaddjacobian.c

src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSingular && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikSingular/cuikaddjacobian.c > CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.i

src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSingular && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikSingular/cuikaddjacobian.c -o CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.s

# Object files for target cuikaddjacobian
cuikaddjacobian_OBJECTS = \
"CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.o"

# External object files for target cuikaddjacobian
cuikaddjacobian_EXTERNAL_OBJECTS =

../bin/cuikaddjacobian: src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/cuikaddjacobian.o
../bin/cuikaddjacobian: src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/build.make
../bin/cuikaddjacobian: ../lib/libcuikworld-common.so.3.1.0
../bin/cuikaddjacobian: ../lib/libcuikplot-common.so.3.1.0
../bin/cuikaddjacobian: /usr/lib/libsolid.so
../bin/cuikaddjacobian: ../lib/libcuikvcollide.so.3.1.0
../bin/cuikaddjacobian: /usr/lib/libVCollide.so
../bin/cuikaddjacobian: /usr/lib/libRAPID.so
../bin/cuikaddjacobian: ../lib/libcuikpqp.so.3.1.0
../bin/cuikaddjacobian: /usr/lib/libPQP.so
../bin/cuikaddjacobian: ../lib/libcuikfcl.so.3.1.0
../bin/cuikaddjacobian: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuikaddjacobian: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuikaddjacobian: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuikaddjacobian: ../lib/libcuikbullet.so.3.1.0
../bin/cuikaddjacobian: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuikaddjacobian: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuikaddjacobian: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuikaddjacobian: ../lib/libcuik-common.so.3.1.0
../bin/cuikaddjacobian: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikaddjacobian: /usr/lib/libexpokit.so
../bin/cuikaddjacobian: /usr/local/lib/libglpk.so
../bin/cuikaddjacobian: /usr/local/lib/libgsl.so
../bin/cuikaddjacobian: /usr/lib/libRigidCLL.so
../bin/cuikaddjacobian: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuikaddjacobian: src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/cuikaddjacobian"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSingular && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikaddjacobian.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/build: ../bin/cuikaddjacobian

.PHONY : src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/build

src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikSingular && $(CMAKE_COMMAND) -P CMakeFiles/cuikaddjacobian.dir/cmake_clean.cmake
.PHONY : src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/clean

src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikSingular /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikSingular /home/logan/Downloads/CuikSuite3/build/src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikSingular/CMakeFiles/cuikaddjacobian.dir/depend

