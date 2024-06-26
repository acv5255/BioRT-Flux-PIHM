# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir

# Include any dependencies generated for this target.
include src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/compiler_depend.make

# Include the progress variables for this target.
include src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/progress.make

# Include the compile flags for this target's objects.
include src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/flags.make

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.o: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/flags.make
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.o: /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sunlinsol/pcg/sunlinsol_pcg.c
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.o: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.o"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.o -MF CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.o.d -o CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.o -c /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sunlinsol/pcg/sunlinsol_pcg.c

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.i"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sunlinsol/pcg/sunlinsol_pcg.c > CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.i

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.s"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sunlinsol/pcg/sunlinsol_pcg.c -o CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.s

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.o: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/flags.make
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.o: /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_math.c
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.o: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.o"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.o -MF CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.o.d -o CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.o -c /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_math.c

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.i"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_math.c > CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.i

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.s"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_math.c -o CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.s

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.o: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/flags.make
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.o: /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_nvector.c
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.o: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.o"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.o -MF CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.o.d -o CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.o -c /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_nvector.c

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.i"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_nvector.c > CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.i

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.s"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_nvector.c -o CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.s

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.o: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/flags.make
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.o: /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_linearsolver.c
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.o: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.o"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.o -MF CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.o.d -o CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.o -c /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_linearsolver.c

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.i"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_linearsolver.c > CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.i

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.s"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_linearsolver.c -o CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.s

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.o: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/flags.make
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.o: /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_iterative.c
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.o: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.o"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.o -MF CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.o.d -o CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.o -c /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_iterative.c

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.i"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_iterative.c > CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.i

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.s"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sundials/sundials_iterative.c -o CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.s

# Object files for target sundials_sunlinsolpcg_static
sundials_sunlinsolpcg_static_OBJECTS = \
"CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.o" \
"CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.o" \
"CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.o" \
"CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.o" \
"CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.o"

# External object files for target sundials_sunlinsolpcg_static
sundials_sunlinsolpcg_static_EXTERNAL_OBJECTS =

src/sunlinsol/pcg/libsundials_sunlinsolpcg.a: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/sunlinsol_pcg.c.o
src/sunlinsol/pcg/libsundials_sunlinsolpcg.a: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_math.c.o
src/sunlinsol/pcg/libsundials_sunlinsolpcg.a: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_nvector.c.o
src/sunlinsol/pcg/libsundials_sunlinsolpcg.a: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_linearsolver.c.o
src/sunlinsol/pcg/libsundials_sunlinsolpcg.a: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/__/__/sundials/sundials_iterative.c.o
src/sunlinsol/pcg/libsundials_sunlinsolpcg.a: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/build.make
src/sunlinsol/pcg/libsundials_sunlinsolpcg.a: src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C static library libsundials_sunlinsolpcg.a"
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && $(CMAKE_COMMAND) -P CMakeFiles/sundials_sunlinsolpcg_static.dir/cmake_clean_target.cmake
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sundials_sunlinsolpcg_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/build: src/sunlinsol/pcg/libsundials_sunlinsolpcg.a
.PHONY : src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/build

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/clean:
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg && $(CMAKE_COMMAND) -P CMakeFiles/sundials_sunlinsolpcg_static.dir/cmake_clean.cmake
.PHONY : src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/clean

src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/depend:
	cd /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/src/sunlinsol/pcg /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg /home/andrew/Documents/Research/Projects/BioRT-Flux-PIHM-py/BioRT-Flux-PIHM/cvode/instdir/src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/sunlinsol/pcg/CMakeFiles/sundials_sunlinsolpcg_static.dir/depend

