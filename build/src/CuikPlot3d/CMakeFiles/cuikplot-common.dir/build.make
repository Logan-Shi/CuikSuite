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
include src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/depend.make

# Include the progress variables for this target.
include src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/flags.make

src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/plot3d.o: src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/flags.make
src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/plot3d.o: ../src/CuikPlot3d/plot3d.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/plot3d.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikplot-common.dir/plot3d.o   -c /home/logan/Downloads/CuikSuite3/src/CuikPlot3d/plot3d.c

src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/plot3d.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikplot-common.dir/plot3d.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikPlot3d/plot3d.c > CMakeFiles/cuikplot-common.dir/plot3d.i

src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/plot3d.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikplot-common.dir/plot3d.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikPlot3d/plot3d.c -o CMakeFiles/cuikplot-common.dir/plot3d.s

src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/color.o: src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/flags.make
src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/color.o: ../src/CuikPlot3d/color.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/color.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikplot-common.dir/color.o   -c /home/logan/Downloads/CuikSuite3/src/CuikPlot3d/color.c

src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/color.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikplot-common.dir/color.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikPlot3d/color.c > CMakeFiles/cuikplot-common.dir/color.i

src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/color.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikplot-common.dir/color.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikPlot3d/color.c -o CMakeFiles/cuikplot-common.dir/color.s

# Object files for target cuikplot-common
cuikplot__common_OBJECTS = \
"CMakeFiles/cuikplot-common.dir/plot3d.o" \
"CMakeFiles/cuikplot-common.dir/color.o"

# External object files for target cuikplot-common
cuikplot__common_EXTERNAL_OBJECTS =

../lib/libcuikplot-common.so.3.1.0: src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/plot3d.o
../lib/libcuikplot-common.so.3.1.0: src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/color.o
../lib/libcuikplot-common.so.3.1.0: src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/build.make
../lib/libcuikplot-common.so.3.1.0: ../lib/libcuik-common.so.3.1.0
../lib/libcuikplot-common.so.3.1.0: /usr/lib/x86_64-linux-gnu/libblas.so
../lib/libcuikplot-common.so.3.1.0: /usr/lib/libexpokit.so
../lib/libcuikplot-common.so.3.1.0: /usr/local/lib/libglpk.so
../lib/libcuikplot-common.so.3.1.0: /usr/local/lib/libgsl.so
../lib/libcuikplot-common.so.3.1.0: src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C shared library ../../../lib/libcuikplot-common.so"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikplot-common.dir/link.txt --verbose=$(VERBOSE)
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d && $(CMAKE_COMMAND) -E cmake_symlink_library ../../../lib/libcuikplot-common.so.3.1.0 ../../../lib/libcuikplot-common.so.3 ../../../lib/libcuikplot-common.so

../lib/libcuikplot-common.so.3: ../lib/libcuikplot-common.so.3.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate ../lib/libcuikplot-common.so.3

../lib/libcuikplot-common.so: ../lib/libcuikplot-common.so.3.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate ../lib/libcuikplot-common.so

# Rule to build all files generated by this target.
src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/build: ../lib/libcuikplot-common.so

.PHONY : src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/build

src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d && $(CMAKE_COMMAND) -P CMakeFiles/cuikplot-common.dir/cmake_clean.cmake
.PHONY : src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/clean

src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikPlot3d /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d /home/logan/Downloads/CuikSuite3/build/src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikPlot3d/CMakeFiles/cuikplot-common.dir/depend
