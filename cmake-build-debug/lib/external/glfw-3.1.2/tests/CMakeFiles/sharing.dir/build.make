# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Programming\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Programming\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\Programming\CLion - Projects\Pool-Table"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug"

# Include any dependencies generated for this target.
include lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/depend.make

# Include the progress variables for this target.
include lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/progress.make

# Include the compile flags for this target's objects.
include lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/flags.make

lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj: lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/flags.make
lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj: lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/includes_C.rsp
lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj: ../lib/external/glfw-3.1.2/tests/sharing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj"
	cd /d "E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests" && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\sharing.dir\sharing.c.obj   -c "E:\Programming\CLion - Projects\Pool-Table\lib\external\glfw-3.1.2\tests\sharing.c"

lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sharing.dir/sharing.c.i"
	cd /d "E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests" && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "E:\Programming\CLion - Projects\Pool-Table\lib\external\glfw-3.1.2\tests\sharing.c" > CMakeFiles\sharing.dir\sharing.c.i

lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sharing.dir/sharing.c.s"
	cd /d "E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests" && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "E:\Programming\CLion - Projects\Pool-Table\lib\external\glfw-3.1.2\tests\sharing.c" -o CMakeFiles\sharing.dir\sharing.c.s

# Object files for target sharing
sharing_OBJECTS = \
"CMakeFiles/sharing.dir/sharing.c.obj"

# External object files for target sharing
sharing_EXTERNAL_OBJECTS =

lib/external/glfw-3.1.2/tests/sharing.exe: lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/sharing.c.obj
lib/external/glfw-3.1.2/tests/sharing.exe: lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/build.make
lib/external/glfw-3.1.2/tests/sharing.exe: lib/external/glfw-3.1.2/src/libglfw3.a
lib/external/glfw-3.1.2/tests/sharing.exe: lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/linklibs.rsp
lib/external/glfw-3.1.2/tests/sharing.exe: lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/objects1.rsp
lib/external/glfw-3.1.2/tests/sharing.exe: lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable sharing.exe"
	cd /d "E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\sharing.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/build: lib/external/glfw-3.1.2/tests/sharing.exe

.PHONY : lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/build

lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/clean:
	cd /d "E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests" && $(CMAKE_COMMAND) -P CMakeFiles\sharing.dir\cmake_clean.cmake
.PHONY : lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/clean

lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "E:\Programming\CLion - Projects\Pool-Table" "E:\Programming\CLion - Projects\Pool-Table\lib\external\glfw-3.1.2\tests" "E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug" "E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests" "E:\Programming\CLion - Projects\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests\CMakeFiles\sharing.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : lib/external/glfw-3.1.2/tests/CMakeFiles/sharing.dir/depend

