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
include src/CuikAnimate/CMakeFiles/cuikplay.dir/depend.make

# Include the progress variables for this target.
include src/CuikAnimate/CMakeFiles/cuikplay.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikAnimate/CMakeFiles/cuikplay.dir/flags.make

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay.o: src/CuikAnimate/CMakeFiles/cuikplay.dir/flags.make
src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay.o: ../src/CuikAnimate/cuikplay.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikplay.dir/cuikplay.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay.c

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikplay.dir/cuikplay.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay.c > CMakeFiles/cuikplay.dir/cuikplay.i

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikplay.dir/cuikplay.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay.c -o CMakeFiles/cuikplay.dir/cuikplay.s

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_callbacks.o: src/CuikAnimate/CMakeFiles/cuikplay.dir/flags.make
src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_callbacks.o: ../src/CuikAnimate/cuikplay_callbacks.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_callbacks.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikplay.dir/cuikplay_callbacks.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay_callbacks.c

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_callbacks.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikplay.dir/cuikplay_callbacks.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay_callbacks.c > CMakeFiles/cuikplay.dir/cuikplay_callbacks.i

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_callbacks.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikplay.dir/cuikplay_callbacks.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay_callbacks.c -o CMakeFiles/cuikplay.dir/cuikplay_callbacks.s

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_interface.o: src/CuikAnimate/CMakeFiles/cuikplay.dir/flags.make
src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_interface.o: ../src/CuikAnimate/cuikplay_interface.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_interface.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikplay.dir/cuikplay_interface.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay_interface.c

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_interface.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikplay.dir/cuikplay_interface.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay_interface.c > CMakeFiles/cuikplay.dir/cuikplay_interface.i

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_interface.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikplay.dir/cuikplay_interface.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay_interface.c -o CMakeFiles/cuikplay.dir/cuikplay_interface.s

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_support.o: src/CuikAnimate/CMakeFiles/cuikplay.dir/flags.make
src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_support.o: ../src/CuikAnimate/cuikplay_support.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_support.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cuikplay.dir/cuikplay_support.o   -c /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay_support.c

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_support.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cuikplay.dir/cuikplay_support.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay_support.c > CMakeFiles/cuikplay.dir/cuikplay_support.i

src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_support.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cuikplay.dir/cuikplay_support.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && mpicc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikAnimate/cuikplay_support.c -o CMakeFiles/cuikplay.dir/cuikplay_support.s

# Object files for target cuikplay
cuikplay_OBJECTS = \
"CMakeFiles/cuikplay.dir/cuikplay.o" \
"CMakeFiles/cuikplay.dir/cuikplay_callbacks.o" \
"CMakeFiles/cuikplay.dir/cuikplay_interface.o" \
"CMakeFiles/cuikplay.dir/cuikplay_support.o"

# External object files for target cuikplay
cuikplay_EXTERNAL_OBJECTS =

../bin/cuikplay: src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay.o
../bin/cuikplay: src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_callbacks.o
../bin/cuikplay: src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_interface.o
../bin/cuikplay: src/CuikAnimate/CMakeFiles/cuikplay.dir/cuikplay_support.o
../bin/cuikplay: src/CuikAnimate/CMakeFiles/cuikplay.dir/build.make
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libglib-2.0.so
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libgtk-x11-2.0.so
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libgdk-x11-2.0.so
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libgobject-2.0.so
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libatk-1.0.so
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libgdk_pixbuf-2.0.so
../bin/cuikplay: ../lib/libcuikatlas-common.so.3.1.0
../bin/cuikplay: ../lib/libcuikworld-common.so.3.1.0
../bin/cuikplay: ../lib/libcuikplot-common.so.3.1.0
../bin/cuikplay: /usr/lib/libsolid.so
../bin/cuikplay: ../lib/libcuikvcollide.so.3.1.0
../bin/cuikplay: /usr/lib/libVCollide.so
../bin/cuikplay: /usr/lib/libRAPID.so
../bin/cuikplay: ../lib/libcuikpqp.so.3.1.0
../bin/cuikplay: /usr/lib/libPQP.so
../bin/cuikplay: ../lib/libcuikfcl.so.3.1.0
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libfcl.so
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libccd.so
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libboost_system.so
../bin/cuikplay: ../lib/libcuikbullet.so.3.1.0
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libBulletCollision.so
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libLinearMath.so
../bin/cuikplay: ../lib/libcuikrigidCLL.so.3.1.0
../bin/cuikplay: ../lib/libcuik-common.so.3.1.0
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libblas.so
../bin/cuikplay: /usr/lib/libexpokit.so
../bin/cuikplay: /usr/local/lib/libglpk.so
../bin/cuikplay: /usr/local/lib/libgsl.so
../bin/cuikplay: /usr/lib/libRigidCLL.so
../bin/cuikplay: /usr/lib/x86_64-linux-gnu/libassimp.so
../bin/cuikplay: /usr/lib/libcuik-kdtree.so
../bin/cuikplay: src/CuikAnimate/CMakeFiles/cuikplay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ../../../bin/cuikplay"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikplay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CuikAnimate/CMakeFiles/cuikplay.dir/build: ../bin/cuikplay

.PHONY : src/CuikAnimate/CMakeFiles/cuikplay.dir/build

src/CuikAnimate/CMakeFiles/cuikplay.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate && $(CMAKE_COMMAND) -P CMakeFiles/cuikplay.dir/cmake_clean.cmake
.PHONY : src/CuikAnimate/CMakeFiles/cuikplay.dir/clean

src/CuikAnimate/CMakeFiles/cuikplay.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikAnimate /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate /home/logan/Downloads/CuikSuite3/build/src/CuikAnimate/CMakeFiles/cuikplay.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikAnimate/CMakeFiles/cuikplay.dir/depend

