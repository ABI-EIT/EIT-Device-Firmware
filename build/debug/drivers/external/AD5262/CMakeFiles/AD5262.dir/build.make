# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\acre018\github\teensy36_boilerplate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\acre018\github\teensy36_boilerplate\_build\debug

# Include any dependencies generated for this target.
include drivers/external/AD5262/CMakeFiles/AD5262.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include drivers/external/AD5262/CMakeFiles/AD5262.dir/compiler_depend.make

# Include the progress variables for this target.
include drivers/external/AD5262/CMakeFiles/AD5262.dir/progress.make

# Include the compile flags for this target's objects.
include drivers/external/AD5262/CMakeFiles/AD5262.dir/flags.make

drivers/external/AD5262/CMakeFiles/AD5262.dir/AD5262.cpp.obj: drivers/external/AD5262/CMakeFiles/AD5262.dir/flags.make
drivers/external/AD5262/CMakeFiles/AD5262.dir/AD5262.cpp.obj: C:/Users/acre018/github/teensy36_boilerplate/drivers/external/AD5262/AD5262.cpp
drivers/external/AD5262/CMakeFiles/AD5262.dir/AD5262.cpp.obj: drivers/external/AD5262/CMakeFiles/AD5262.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\acre018\github\teensy36_boilerplate\_build\debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object drivers/external/AD5262/CMakeFiles/AD5262.dir/AD5262.cpp.obj"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\AD5262 && C:\PROGRA~2\ARMGNU~1\112202~1.02\bin\arm-none-eabi-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT drivers/external/AD5262/CMakeFiles/AD5262.dir/AD5262.cpp.obj -MF CMakeFiles\AD5262.dir\AD5262.cpp.obj.d -o CMakeFiles\AD5262.dir\AD5262.cpp.obj -c C:\Users\acre018\github\teensy36_boilerplate\drivers\external\AD5262\AD5262.cpp

drivers/external/AD5262/CMakeFiles/AD5262.dir/AD5262.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AD5262.dir/AD5262.cpp.i"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\AD5262 && C:\PROGRA~2\ARMGNU~1\112202~1.02\bin\arm-none-eabi-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\acre018\github\teensy36_boilerplate\drivers\external\AD5262\AD5262.cpp > CMakeFiles\AD5262.dir\AD5262.cpp.i

drivers/external/AD5262/CMakeFiles/AD5262.dir/AD5262.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AD5262.dir/AD5262.cpp.s"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\AD5262 && C:\PROGRA~2\ARMGNU~1\112202~1.02\bin\arm-none-eabi-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\acre018\github\teensy36_boilerplate\drivers\external\AD5262\AD5262.cpp -o CMakeFiles\AD5262.dir\AD5262.cpp.s

# Object files for target AD5262
AD5262_OBJECTS = \
"CMakeFiles/AD5262.dir/AD5262.cpp.obj"

# External object files for target AD5262
AD5262_EXTERNAL_OBJECTS =

drivers/external/AD5262/libAD5262.a: drivers/external/AD5262/CMakeFiles/AD5262.dir/AD5262.cpp.obj
drivers/external/AD5262/libAD5262.a: drivers/external/AD5262/CMakeFiles/AD5262.dir/build.make
drivers/external/AD5262/libAD5262.a: drivers/external/AD5262/CMakeFiles/AD5262.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\acre018\github\teensy36_boilerplate\_build\debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libAD5262.a"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\AD5262 && $(CMAKE_COMMAND) -P CMakeFiles\AD5262.dir\cmake_clean_target.cmake
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\AD5262 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\AD5262.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
drivers/external/AD5262/CMakeFiles/AD5262.dir/build: drivers/external/AD5262/libAD5262.a
.PHONY : drivers/external/AD5262/CMakeFiles/AD5262.dir/build

drivers/external/AD5262/CMakeFiles/AD5262.dir/clean:
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\AD5262 && $(CMAKE_COMMAND) -P CMakeFiles\AD5262.dir\cmake_clean.cmake
.PHONY : drivers/external/AD5262/CMakeFiles/AD5262.dir/clean

drivers/external/AD5262/CMakeFiles/AD5262.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\acre018\github\teensy36_boilerplate C:\Users\acre018\github\teensy36_boilerplate\drivers\external\AD5262 C:\Users\acre018\github\teensy36_boilerplate\_build\debug C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\AD5262 C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\AD5262\CMakeFiles\AD5262.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : drivers/external/AD5262/CMakeFiles/AD5262.dir/depend

