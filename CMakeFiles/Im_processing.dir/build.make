# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/leonardo/Workbench/neurowood-0.0.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leonardo/Workbench/neurowood-0.0.2

# Include any dependencies generated for this target.
include CMakeFiles/Im_processing.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Im_processing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Im_processing.dir/flags.make

CMakeFiles/Im_processing.dir/Im_processing.cpp.o: CMakeFiles/Im_processing.dir/flags.make
CMakeFiles/Im_processing.dir/Im_processing.cpp.o: Im_processing.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/leonardo/Workbench/neurowood-0.0.2/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Im_processing.dir/Im_processing.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Im_processing.dir/Im_processing.cpp.o -c /home/leonardo/Workbench/neurowood-0.0.2/Im_processing.cpp

CMakeFiles/Im_processing.dir/Im_processing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Im_processing.dir/Im_processing.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/leonardo/Workbench/neurowood-0.0.2/Im_processing.cpp > CMakeFiles/Im_processing.dir/Im_processing.cpp.i

CMakeFiles/Im_processing.dir/Im_processing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Im_processing.dir/Im_processing.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/leonardo/Workbench/neurowood-0.0.2/Im_processing.cpp -o CMakeFiles/Im_processing.dir/Im_processing.cpp.s

CMakeFiles/Im_processing.dir/Im_processing.cpp.o.requires:
.PHONY : CMakeFiles/Im_processing.dir/Im_processing.cpp.o.requires

CMakeFiles/Im_processing.dir/Im_processing.cpp.o.provides: CMakeFiles/Im_processing.dir/Im_processing.cpp.o.requires
	$(MAKE) -f CMakeFiles/Im_processing.dir/build.make CMakeFiles/Im_processing.dir/Im_processing.cpp.o.provides.build
.PHONY : CMakeFiles/Im_processing.dir/Im_processing.cpp.o.provides

CMakeFiles/Im_processing.dir/Im_processing.cpp.o.provides.build: CMakeFiles/Im_processing.dir/Im_processing.cpp.o

# Object files for target Im_processing
Im_processing_OBJECTS = \
"CMakeFiles/Im_processing.dir/Im_processing.cpp.o"

# External object files for target Im_processing
Im_processing_EXTERNAL_OBJECTS =

libIm_processing.a: CMakeFiles/Im_processing.dir/Im_processing.cpp.o
libIm_processing.a: CMakeFiles/Im_processing.dir/build.make
libIm_processing.a: CMakeFiles/Im_processing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libIm_processing.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Im_processing.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Im_processing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Im_processing.dir/build: libIm_processing.a
.PHONY : CMakeFiles/Im_processing.dir/build

CMakeFiles/Im_processing.dir/requires: CMakeFiles/Im_processing.dir/Im_processing.cpp.o.requires
.PHONY : CMakeFiles/Im_processing.dir/requires

CMakeFiles/Im_processing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Im_processing.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Im_processing.dir/clean

CMakeFiles/Im_processing.dir/depend:
	cd /home/leonardo/Workbench/neurowood-0.0.2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leonardo/Workbench/neurowood-0.0.2 /home/leonardo/Workbench/neurowood-0.0.2 /home/leonardo/Workbench/neurowood-0.0.2 /home/leonardo/Workbench/neurowood-0.0.2 /home/leonardo/Workbench/neurowood-0.0.2/CMakeFiles/Im_processing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Im_processing.dir/depend

