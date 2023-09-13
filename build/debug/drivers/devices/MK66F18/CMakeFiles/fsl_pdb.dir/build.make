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
include drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/compiler_depend.make

# Include the progress variables for this target.
include drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/progress.make

# Include the compile flags for this target's objects.
include drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/flags.make

drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.obj: drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/flags.make
drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.obj: C:/Users/acre018/github/teensy36_boilerplate/drivers/devices/MK66F18/drivers/fsl_pdb.c
drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.obj: drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\acre018\github\teensy36_boilerplate\_build\debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.obj"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\devices\MK66F18 && C:\PROGRA~2\ARMGNU~1\112202~1.02\bin\arm-none-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.obj -MF CMakeFiles\fsl_pdb.dir\drivers\fsl_pdb.c.obj.d -o CMakeFiles\fsl_pdb.dir\drivers\fsl_pdb.c.obj -c C:\Users\acre018\github\teensy36_boilerplate\drivers\devices\MK66F18\drivers\fsl_pdb.c

drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.i"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\devices\MK66F18 && C:\PROGRA~2\ARMGNU~1\112202~1.02\bin\arm-none-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\acre018\github\teensy36_boilerplate\drivers\devices\MK66F18\drivers\fsl_pdb.c > CMakeFiles\fsl_pdb.dir\drivers\fsl_pdb.c.i

drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.s"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\devices\MK66F18 && C:\PROGRA~2\ARMGNU~1\112202~1.02\bin\arm-none-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\acre018\github\teensy36_boilerplate\drivers\devices\MK66F18\drivers\fsl_pdb.c -o CMakeFiles\fsl_pdb.dir\drivers\fsl_pdb.c.s

# Object files for target fsl_pdb
fsl_pdb_OBJECTS = \
"CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.obj"

# External object files for target fsl_pdb
fsl_pdb_EXTERNAL_OBJECTS =

drivers/devices/MK66F18/libfsl_pdb.a: drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/drivers/fsl_pdb.c.obj
drivers/devices/MK66F18/libfsl_pdb.a: drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/build.make
drivers/devices/MK66F18/libfsl_pdb.a: drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\acre018\github\teensy36_boilerplate\_build\debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libfsl_pdb.a"
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\devices\MK66F18 && $(CMAKE_COMMAND) -P CMakeFiles\fsl_pdb.dir\cmake_clean_target.cmake
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\devices\MK66F18 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\fsl_pdb.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/build: drivers/devices/MK66F18/libfsl_pdb.a
.PHONY : drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/build

drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/clean:
	cd /d C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\devices\MK66F18 && $(CMAKE_COMMAND) -P CMakeFiles\fsl_pdb.dir\cmake_clean.cmake
.PHONY : drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/clean

drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\acre018\github\teensy36_boilerplate C:\Users\acre018\github\teensy36_boilerplate\drivers\devices\MK66F18 C:\Users\acre018\github\teensy36_boilerplate\_build\debug C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\devices\MK66F18 C:\Users\acre018\github\teensy36_boilerplate\_build\debug\drivers\devices\MK66F18\CMakeFiles\fsl_pdb.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : drivers/devices/MK66F18/CMakeFiles/fsl_pdb.dir/depend

