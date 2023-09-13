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
include drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/compiler_depend.make

# Include the progress variables for this target.
include drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/progress.make

# Include the compile flags for this target's objects.
include drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/flags.make

drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.obj: drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/flags.make
drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.obj: C:/Users/acre018/github/teensy36_boilerplate/drivers/external/CD74HC4067/CD74HC4067.cpp
drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.obj: drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\acre018\github\teensy36_boilerplate\_build\debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.obj"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\CD74HC4067 && C:\PROGRA~2\ARMGNU~1\112202~1.02\bin\arm-none-eabi-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.obj -MF CMakeFiles\CD74HC4067.dir\CD74HC4067.cpp.obj.d -o CMakeFiles\CD74HC4067.dir\CD74HC4067.cpp.obj -c C:\Users\acre018\github\teensy36_boilerplate\drivers\external\CD74HC4067\CD74HC4067.cpp

drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.i"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\CD74HC4067 && C:\PROGRA~2\ARMGNU~1\112202~1.02\bin\arm-none-eabi-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\acre018\github\teensy36_boilerplate\drivers\external\CD74HC4067\CD74HC4067.cpp > CMakeFiles\CD74HC4067.dir\CD74HC4067.cpp.i

drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.s"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\CD74HC4067 && C:\PROGRA~2\ARMGNU~1\112202~1.02\bin\arm-none-eabi-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\acre018\github\teensy36_boilerplate\drivers\external\CD74HC4067\CD74HC4067.cpp -o CMakeFiles\CD74HC4067.dir\CD74HC4067.cpp.s

# Object files for target CD74HC4067
CD74HC4067_OBJECTS = \
"CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.obj"

# External object files for target CD74HC4067
CD74HC4067_EXTERNAL_OBJECTS =

drivers/external/CD74HC4067/libCD74HC4067.a: drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/CD74HC4067.cpp.obj
drivers/external/CD74HC4067/libCD74HC4067.a: drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/build.make
drivers/external/CD74HC4067/libCD74HC4067.a: drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\acre018\github\teensy36_boilerplate\_build\debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCD74HC4067.a"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\CD74HC4067 && $(CMAKE_COMMAND) -P CMakeFiles\CD74HC4067.dir\cmake_clean_target.cmake
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\CD74HC4067 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CD74HC4067.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/build: drivers/external/CD74HC4067/libCD74HC4067.a
.PHONY : drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/build

drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/clean:
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\CD74HC4067 && $(CMAKE_COMMAND) -P CMakeFiles\CD74HC4067.dir\cmake_clean.cmake
.PHONY : drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/clean

drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\acre018\github\teensy36_boilerplate C:\Users\acre018\github\teensy36_boilerplate\drivers\external\CD74HC4067 C:\Users\acre018\github\teensy36_boilerplate\_build\debug C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\CD74HC4067 C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\external\CD74HC4067\CMakeFiles\CD74HC4067.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : drivers/external/CD74HC4067/CMakeFiles/CD74HC4067.dir/depend
