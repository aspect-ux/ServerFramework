# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/linno/Desktop/Project/AspectServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/linno/Desktop/Project/AspectServer/build

# Include any dependencies generated for this target.
include CMakeFiles/aspect.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/aspect.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/aspect.dir/flags.make

CMakeFiles/aspect.dir/aspect/log.cc.o: CMakeFiles/aspect.dir/flags.make
CMakeFiles/aspect.dir/aspect/log.cc.o: ../aspect/log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linno/Desktop/Project/AspectServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/aspect.dir/aspect/log.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) -D__FILE__=\"aspect/log.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aspect.dir/aspect/log.cc.o -c /home/linno/Desktop/Project/AspectServer/aspect/log.cc

CMakeFiles/aspect.dir/aspect/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aspect.dir/aspect/log.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"aspect/log.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linno/Desktop/Project/AspectServer/aspect/log.cc > CMakeFiles/aspect.dir/aspect/log.cc.i

CMakeFiles/aspect.dir/aspect/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aspect.dir/aspect/log.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"aspect/log.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linno/Desktop/Project/AspectServer/aspect/log.cc -o CMakeFiles/aspect.dir/aspect/log.cc.s

CMakeFiles/aspect.dir/aspect/log.cc.o.requires:

.PHONY : CMakeFiles/aspect.dir/aspect/log.cc.o.requires

CMakeFiles/aspect.dir/aspect/log.cc.o.provides: CMakeFiles/aspect.dir/aspect/log.cc.o.requires
	$(MAKE) -f CMakeFiles/aspect.dir/build.make CMakeFiles/aspect.dir/aspect/log.cc.o.provides.build
.PHONY : CMakeFiles/aspect.dir/aspect/log.cc.o.provides

CMakeFiles/aspect.dir/aspect/log.cc.o.provides.build: CMakeFiles/aspect.dir/aspect/log.cc.o


CMakeFiles/aspect.dir/aspect/util.cc.o: CMakeFiles/aspect.dir/flags.make
CMakeFiles/aspect.dir/aspect/util.cc.o: ../aspect/util.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linno/Desktop/Project/AspectServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/aspect.dir/aspect/util.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) -D__FILE__=\"aspect/util.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aspect.dir/aspect/util.cc.o -c /home/linno/Desktop/Project/AspectServer/aspect/util.cc

CMakeFiles/aspect.dir/aspect/util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aspect.dir/aspect/util.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"aspect/util.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linno/Desktop/Project/AspectServer/aspect/util.cc > CMakeFiles/aspect.dir/aspect/util.cc.i

CMakeFiles/aspect.dir/aspect/util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aspect.dir/aspect/util.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"aspect/util.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linno/Desktop/Project/AspectServer/aspect/util.cc -o CMakeFiles/aspect.dir/aspect/util.cc.s

CMakeFiles/aspect.dir/aspect/util.cc.o.requires:

.PHONY : CMakeFiles/aspect.dir/aspect/util.cc.o.requires

CMakeFiles/aspect.dir/aspect/util.cc.o.provides: CMakeFiles/aspect.dir/aspect/util.cc.o.requires
	$(MAKE) -f CMakeFiles/aspect.dir/build.make CMakeFiles/aspect.dir/aspect/util.cc.o.provides.build
.PHONY : CMakeFiles/aspect.dir/aspect/util.cc.o.provides

CMakeFiles/aspect.dir/aspect/util.cc.o.provides.build: CMakeFiles/aspect.dir/aspect/util.cc.o


CMakeFiles/aspect.dir/aspect/config.cc.o: CMakeFiles/aspect.dir/flags.make
CMakeFiles/aspect.dir/aspect/config.cc.o: ../aspect/config.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linno/Desktop/Project/AspectServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/aspect.dir/aspect/config.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) -D__FILE__=\"aspect/config.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aspect.dir/aspect/config.cc.o -c /home/linno/Desktop/Project/AspectServer/aspect/config.cc

CMakeFiles/aspect.dir/aspect/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aspect.dir/aspect/config.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"aspect/config.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linno/Desktop/Project/AspectServer/aspect/config.cc > CMakeFiles/aspect.dir/aspect/config.cc.i

CMakeFiles/aspect.dir/aspect/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aspect.dir/aspect/config.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"aspect/config.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linno/Desktop/Project/AspectServer/aspect/config.cc -o CMakeFiles/aspect.dir/aspect/config.cc.s

CMakeFiles/aspect.dir/aspect/config.cc.o.requires:

.PHONY : CMakeFiles/aspect.dir/aspect/config.cc.o.requires

CMakeFiles/aspect.dir/aspect/config.cc.o.provides: CMakeFiles/aspect.dir/aspect/config.cc.o.requires
	$(MAKE) -f CMakeFiles/aspect.dir/build.make CMakeFiles/aspect.dir/aspect/config.cc.o.provides.build
.PHONY : CMakeFiles/aspect.dir/aspect/config.cc.o.provides

CMakeFiles/aspect.dir/aspect/config.cc.o.provides.build: CMakeFiles/aspect.dir/aspect/config.cc.o


CMakeFiles/aspect.dir/aspect/thread.cc.o: CMakeFiles/aspect.dir/flags.make
CMakeFiles/aspect.dir/aspect/thread.cc.o: ../aspect/thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/linno/Desktop/Project/AspectServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/aspect.dir/aspect/thread.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) -D__FILE__=\"aspect/thread.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aspect.dir/aspect/thread.cc.o -c /home/linno/Desktop/Project/AspectServer/aspect/thread.cc

CMakeFiles/aspect.dir/aspect/thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aspect.dir/aspect/thread.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"aspect/thread.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/linno/Desktop/Project/AspectServer/aspect/thread.cc > CMakeFiles/aspect.dir/aspect/thread.cc.i

CMakeFiles/aspect.dir/aspect/thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aspect.dir/aspect/thread.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) -D__FILE__=\"aspect/thread.cc\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/linno/Desktop/Project/AspectServer/aspect/thread.cc -o CMakeFiles/aspect.dir/aspect/thread.cc.s

CMakeFiles/aspect.dir/aspect/thread.cc.o.requires:

.PHONY : CMakeFiles/aspect.dir/aspect/thread.cc.o.requires

CMakeFiles/aspect.dir/aspect/thread.cc.o.provides: CMakeFiles/aspect.dir/aspect/thread.cc.o.requires
	$(MAKE) -f CMakeFiles/aspect.dir/build.make CMakeFiles/aspect.dir/aspect/thread.cc.o.provides.build
.PHONY : CMakeFiles/aspect.dir/aspect/thread.cc.o.provides

CMakeFiles/aspect.dir/aspect/thread.cc.o.provides.build: CMakeFiles/aspect.dir/aspect/thread.cc.o


# Object files for target aspect
aspect_OBJECTS = \
"CMakeFiles/aspect.dir/aspect/log.cc.o" \
"CMakeFiles/aspect.dir/aspect/util.cc.o" \
"CMakeFiles/aspect.dir/aspect/config.cc.o" \
"CMakeFiles/aspect.dir/aspect/thread.cc.o"

# External object files for target aspect
aspect_EXTERNAL_OBJECTS =

../lib/libaspect.so: CMakeFiles/aspect.dir/aspect/log.cc.o
../lib/libaspect.so: CMakeFiles/aspect.dir/aspect/util.cc.o
../lib/libaspect.so: CMakeFiles/aspect.dir/aspect/config.cc.o
../lib/libaspect.so: CMakeFiles/aspect.dir/aspect/thread.cc.o
../lib/libaspect.so: CMakeFiles/aspect.dir/build.make
../lib/libaspect.so: CMakeFiles/aspect.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/linno/Desktop/Project/AspectServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library ../lib/libaspect.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aspect.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/aspect.dir/build: ../lib/libaspect.so

.PHONY : CMakeFiles/aspect.dir/build

CMakeFiles/aspect.dir/requires: CMakeFiles/aspect.dir/aspect/log.cc.o.requires
CMakeFiles/aspect.dir/requires: CMakeFiles/aspect.dir/aspect/util.cc.o.requires
CMakeFiles/aspect.dir/requires: CMakeFiles/aspect.dir/aspect/config.cc.o.requires
CMakeFiles/aspect.dir/requires: CMakeFiles/aspect.dir/aspect/thread.cc.o.requires

.PHONY : CMakeFiles/aspect.dir/requires

CMakeFiles/aspect.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/aspect.dir/cmake_clean.cmake
.PHONY : CMakeFiles/aspect.dir/clean

CMakeFiles/aspect.dir/depend:
	cd /home/linno/Desktop/Project/AspectServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/linno/Desktop/Project/AspectServer /home/linno/Desktop/Project/AspectServer /home/linno/Desktop/Project/AspectServer/build /home/linno/Desktop/Project/AspectServer/build /home/linno/Desktop/Project/AspectServer/build/CMakeFiles/aspect.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/aspect.dir/depend

