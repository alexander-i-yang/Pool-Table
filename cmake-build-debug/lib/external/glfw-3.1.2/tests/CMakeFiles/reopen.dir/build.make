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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Samuel\Documents\Coding\LASA\Pool-Table

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug

# Include any dependencies generated for this target.
include lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/depend.make

# Include the progress variables for this target.
include lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/progress.make

# Include the compile flags for this target's objects.
include lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/flags.make

lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.obj: lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/flags.make
lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.obj: lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/includes_C.rsp
lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.obj: ../lib/external/glfw-3.1.2/tests/reopen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.obj"
	cd /d C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests && C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\reopen.dir\reopen.c.obj   -c C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\lib\external\glfw-3.1.2\tests\reopen.c

lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reopen.dir/reopen.c.i"
	cd /d C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests && C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\lib\external\glfw-3.1.2\tests\reopen.c > CMakeFiles\reopen.dir\reopen.c.i

lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reopen.dir/reopen.c.s"
	cd /d C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests && C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\lib\external\glfw-3.1.2\tests\reopen.c -o CMakeFiles\reopen.dir\reopen.c.s

# Object files for target reopen
reopen_OBJECTS = \
"CMakeFiles/reopen.dir/reopen.c.obj"

# External object files for target reopen
reopen_EXTERNAL_OBJECTS =

lib/external/glfw-3.1.2/tests/reopen.exe: lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/reopen.c.obj
lib/external/glfw-3.1.2/tests/reopen.exe: lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/build.make
lib/external/glfw-3.1.2/tests/reopen.exe: lib/external/glfw-3.1.2/src/libglfw3.a
lib/external/glfw-3.1.2/tests/reopen.exe: lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/linklibs.rsp
lib/external/glfw-3.1.2/tests/reopen.exe: lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/objects1.rsp
lib/external/glfw-3.1.2/tests/reopen.exe: lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable reopen.exe"
	cd /d C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\reopen.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/build: lib/external/glfw-3.1.2/tests/reopen.exe

.PHONY : lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/build

lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/clean:
	cd /d C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests && $(CMAKE_COMMAND) -P CMakeFiles\reopen.dir\cmake_clean.cmake
.PHONY : lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/clean

lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Samuel\Documents\Coding\LASA\Pool-Table C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\lib\external\glfw-3.1.2\tests C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests C:\Users\Samuel\Documents\Coding\LASA\Pool-Table\cmake-build-debug\lib\external\glfw-3.1.2\tests\CMakeFiles\reopen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : lib/external/glfw-3.1.2/tests/CMakeFiles/reopen.dir/depend

