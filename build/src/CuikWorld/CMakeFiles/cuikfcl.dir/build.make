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
include src/CuikWorld/CMakeFiles/cuikfcl.dir/depend.make

# Include the progress variables for this target.
include src/CuikWorld/CMakeFiles/cuikfcl.dir/progress.make

# Include the compile flags for this target's objects.
include src/CuikWorld/CMakeFiles/cuikfcl.dir/flags.make

src/CuikWorld/CMakeFiles/cuikfcl.dir/cd_fcl.o: src/CuikWorld/CMakeFiles/cuikfcl.dir/flags.make
src/CuikWorld/CMakeFiles/cuikfcl.dir/cd_fcl.o: ../src/CuikWorld/cd_fcl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CuikWorld/CMakeFiles/cuikfcl.dir/cd_fcl.o"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && /usr/bin/g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cuikfcl.dir/cd_fcl.o -c /home/logan/Downloads/CuikSuite3/src/CuikWorld/cd_fcl.cpp

src/CuikWorld/CMakeFiles/cuikfcl.dir/cd_fcl.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cuikfcl.dir/cd_fcl.i"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/logan/Downloads/CuikSuite3/src/CuikWorld/cd_fcl.cpp > CMakeFiles/cuikfcl.dir/cd_fcl.i

src/CuikWorld/CMakeFiles/cuikfcl.dir/cd_fcl.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cuikfcl.dir/cd_fcl.s"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && /usr/bin/g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/logan/Downloads/CuikSuite3/src/CuikWorld/cd_fcl.cpp -o CMakeFiles/cuikfcl.dir/cd_fcl.s

# Object files for target cuikfcl
cuikfcl_OBJECTS = \
"CMakeFiles/cuikfcl.dir/cd_fcl.o"

# External object files for target cuikfcl
cuikfcl_EXTERNAL_OBJECTS =

../lib/libcuikfcl.so.3.1.0: src/CuikWorld/CMakeFiles/cuikfcl.dir/cd_fcl.o
../lib/libcuikfcl.so.3.1.0: src/CuikWorld/CMakeFiles/cuikfcl.dir/build.make
../lib/libcuikfcl.so.3.1.0: /usr/lib/x86_64-linux-gnu/libfcl.so
../lib/libcuikfcl.so.3.1.0: /usr/lib/x86_64-linux-gnu/libccd.so
../lib/libcuikfcl.so.3.1.0: /usr/lib/x86_64-linux-gnu/libboost_system.so
../lib/libcuikfcl.so.3.1.0: ../lib/libcuik-common.so.3.1.0
../lib/libcuikfcl.so.3.1.0: /usr/lib/x86_64-linux-gnu/libblas.so
../lib/libcuikfcl.so.3.1.0: /usr/lib/libexpokit.so
../lib/libcuikfcl.so.3.1.0: /usr/local/lib/libglpk.so
../lib/libcuikfcl.so.3.1.0: /usr/local/lib/libgsl.so
../lib/libcuikfcl.so.3.1.0: src/CuikWorld/CMakeFiles/cuikfcl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/logan/Downloads/CuikSuite3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../../../lib/libcuikfcl.so"
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cuikfcl.dir/link.txt --verbose=$(VERBOSE)
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && $(CMAKE_COMMAND) -E cmake_symlink_library ../../../lib/libcuikfcl.so.3.1.0 ../../../lib/libcuikfcl.so.3 ../../../lib/libcuikfcl.so

../lib/libcuikfcl.so.3: ../lib/libcuikfcl.so.3.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate ../lib/libcuikfcl.so.3

../lib/libcuikfcl.so: ../lib/libcuikfcl.so.3.1.0
	@$(CMAKE_COMMAND) -E touch_nocreate ../lib/libcuikfcl.so

# Rule to build all files generated by this target.
src/CuikWorld/CMakeFiles/cuikfcl.dir/build: ../lib/libcuikfcl.so

.PHONY : src/CuikWorld/CMakeFiles/cuikfcl.dir/build

src/CuikWorld/CMakeFiles/cuikfcl.dir/clean:
	cd /home/logan/Downloads/CuikSuite3/build/src/CuikWorld && $(CMAKE_COMMAND) -P CMakeFiles/cuikfcl.dir/cmake_clean.cmake
.PHONY : src/CuikWorld/CMakeFiles/cuikfcl.dir/clean

src/CuikWorld/CMakeFiles/cuikfcl.dir/depend:
	cd /home/logan/Downloads/CuikSuite3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/logan/Downloads/CuikSuite3 /home/logan/Downloads/CuikSuite3/src/CuikWorld /home/logan/Downloads/CuikSuite3/build /home/logan/Downloads/CuikSuite3/build/src/CuikWorld /home/logan/Downloads/CuikSuite3/build/src/CuikWorld/CMakeFiles/cuikfcl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CuikWorld/CMakeFiles/cuikfcl.dir/depend

