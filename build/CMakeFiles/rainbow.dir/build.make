# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /opt/cmake-3.21.1-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.21.1-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/rainbow

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/rainbow/build

# Include any dependencies generated for this target.
include CMakeFiles/rainbow.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rainbow.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rainbow.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rainbow.dir/flags.make

CMakeFiles/rainbow.dir/rainbow/address.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/address.cpp.o: ../rainbow/address.cpp
CMakeFiles/rainbow.dir/rainbow/address.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rainbow.dir/rainbow/address.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/address.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/address.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/address.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/address.cpp.o -c /home/ubuntu/rainbow/rainbow/address.cpp

CMakeFiles/rainbow.dir/rainbow/address.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/address.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/address.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/address.cpp > CMakeFiles/rainbow.dir/rainbow/address.cpp.i

CMakeFiles/rainbow.dir/rainbow/address.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/address.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/address.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/address.cpp -o CMakeFiles/rainbow.dir/rainbow/address.cpp.s

CMakeFiles/rainbow.dir/rainbow/config.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/config.cpp.o: ../rainbow/config.cpp
CMakeFiles/rainbow.dir/rainbow/config.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/rainbow.dir/rainbow/config.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/config.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/config.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/config.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/config.cpp.o -c /home/ubuntu/rainbow/rainbow/config.cpp

CMakeFiles/rainbow.dir/rainbow/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/config.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/config.cpp > CMakeFiles/rainbow.dir/rainbow/config.cpp.i

CMakeFiles/rainbow.dir/rainbow/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/config.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/config.cpp -o CMakeFiles/rainbow.dir/rainbow/config.cpp.s

CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.o: ../rainbow/fd_manager.cpp
CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/fd_manager.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.o -c /home/ubuntu/rainbow/rainbow/fd_manager.cpp

CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/fd_manager.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/fd_manager.cpp > CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.i

CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/fd_manager.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/fd_manager.cpp -o CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.s

CMakeFiles/rainbow.dir/rainbow/fiber.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/fiber.cpp.o: ../rainbow/fiber.cpp
CMakeFiles/rainbow.dir/rainbow/fiber.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/rainbow.dir/rainbow/fiber.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/fiber.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/fiber.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/fiber.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/fiber.cpp.o -c /home/ubuntu/rainbow/rainbow/fiber.cpp

CMakeFiles/rainbow.dir/rainbow/fiber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/fiber.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/fiber.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/fiber.cpp > CMakeFiles/rainbow.dir/rainbow/fiber.cpp.i

CMakeFiles/rainbow.dir/rainbow/fiber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/fiber.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/fiber.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/fiber.cpp -o CMakeFiles/rainbow.dir/rainbow/fiber.cpp.s

CMakeFiles/rainbow.dir/rainbow/hook.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/hook.cpp.o: ../rainbow/hook.cpp
CMakeFiles/rainbow.dir/rainbow/hook.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/rainbow.dir/rainbow/hook.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/hook.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/hook.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/hook.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/hook.cpp.o -c /home/ubuntu/rainbow/rainbow/hook.cpp

CMakeFiles/rainbow.dir/rainbow/hook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/hook.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/hook.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/hook.cpp > CMakeFiles/rainbow.dir/rainbow/hook.cpp.i

CMakeFiles/rainbow.dir/rainbow/hook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/hook.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/hook.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/hook.cpp -o CMakeFiles/rainbow.dir/rainbow/hook.cpp.s

CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.o: ../rainbow/iomanager.cpp
CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/iomanager.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.o -c /home/ubuntu/rainbow/rainbow/iomanager.cpp

CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/iomanager.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/iomanager.cpp > CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.i

CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/iomanager.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/iomanager.cpp -o CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.s

CMakeFiles/rainbow.dir/rainbow/log.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/log.cpp.o: ../rainbow/log.cpp
CMakeFiles/rainbow.dir/rainbow/log.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/rainbow.dir/rainbow/log.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/log.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/log.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/log.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/log.cpp.o -c /home/ubuntu/rainbow/rainbow/log.cpp

CMakeFiles/rainbow.dir/rainbow/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/log.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/log.cpp > CMakeFiles/rainbow.dir/rainbow/log.cpp.i

CMakeFiles/rainbow.dir/rainbow/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/log.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/log.cpp -o CMakeFiles/rainbow.dir/rainbow/log.cpp.s

CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.o: ../rainbow/scheduler.cpp
CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/scheduler.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.o -c /home/ubuntu/rainbow/rainbow/scheduler.cpp

CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/scheduler.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/scheduler.cpp > CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.i

CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/scheduler.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/scheduler.cpp -o CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.s

CMakeFiles/rainbow.dir/rainbow/socket.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/socket.cpp.o: ../rainbow/socket.cpp
CMakeFiles/rainbow.dir/rainbow/socket.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/rainbow.dir/rainbow/socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/socket.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/socket.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/socket.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/socket.cpp.o -c /home/ubuntu/rainbow/rainbow/socket.cpp

CMakeFiles/rainbow.dir/rainbow/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/socket.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/socket.cpp > CMakeFiles/rainbow.dir/rainbow/socket.cpp.i

CMakeFiles/rainbow.dir/rainbow/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/socket.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/socket.cpp -o CMakeFiles/rainbow.dir/rainbow/socket.cpp.s

CMakeFiles/rainbow.dir/rainbow/timer.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/timer.cpp.o: ../rainbow/timer.cpp
CMakeFiles/rainbow.dir/rainbow/timer.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/rainbow.dir/rainbow/timer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/timer.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/timer.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/timer.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/timer.cpp.o -c /home/ubuntu/rainbow/rainbow/timer.cpp

CMakeFiles/rainbow.dir/rainbow/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/timer.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/timer.cpp > CMakeFiles/rainbow.dir/rainbow/timer.cpp.i

CMakeFiles/rainbow.dir/rainbow/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/timer.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/timer.cpp -o CMakeFiles/rainbow.dir/rainbow/timer.cpp.s

CMakeFiles/rainbow.dir/rainbow/thread.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/thread.cpp.o: ../rainbow/thread.cpp
CMakeFiles/rainbow.dir/rainbow/thread.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/rainbow.dir/rainbow/thread.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/thread.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/thread.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/thread.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/thread.cpp.o -c /home/ubuntu/rainbow/rainbow/thread.cpp

CMakeFiles/rainbow.dir/rainbow/thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/thread.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/thread.cpp > CMakeFiles/rainbow.dir/rainbow/thread.cpp.i

CMakeFiles/rainbow.dir/rainbow/thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/thread.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/thread.cpp -o CMakeFiles/rainbow.dir/rainbow/thread.cpp.s

CMakeFiles/rainbow.dir/rainbow/util.cpp.o: CMakeFiles/rainbow.dir/flags.make
CMakeFiles/rainbow.dir/rainbow/util.cpp.o: ../rainbow/util.cpp
CMakeFiles/rainbow.dir/rainbow/util.cpp.o: CMakeFiles/rainbow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/rainbow.dir/rainbow/util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/util.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rainbow.dir/rainbow/util.cpp.o -MF CMakeFiles/rainbow.dir/rainbow/util.cpp.o.d -o CMakeFiles/rainbow.dir/rainbow/util.cpp.o -c /home/ubuntu/rainbow/rainbow/util.cpp

CMakeFiles/rainbow.dir/rainbow/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rainbow.dir/rainbow/util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/util.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/rainbow/rainbow/util.cpp > CMakeFiles/rainbow.dir/rainbow/util.cpp.i

CMakeFiles/rainbow.dir/rainbow/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rainbow.dir/rainbow/util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) -D__FILE__=\"rainbow/util.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/rainbow/rainbow/util.cpp -o CMakeFiles/rainbow.dir/rainbow/util.cpp.s

# Object files for target rainbow
rainbow_OBJECTS = \
"CMakeFiles/rainbow.dir/rainbow/address.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/config.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/fiber.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/hook.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/log.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/socket.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/timer.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/thread.cpp.o" \
"CMakeFiles/rainbow.dir/rainbow/util.cpp.o"

# External object files for target rainbow
rainbow_EXTERNAL_OBJECTS =

librainbow.so: CMakeFiles/rainbow.dir/rainbow/address.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/config.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/fd_manager.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/fiber.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/hook.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/iomanager.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/log.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/scheduler.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/socket.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/timer.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/thread.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/rainbow/util.cpp.o
librainbow.so: CMakeFiles/rainbow.dir/build.make
librainbow.so: CMakeFiles/rainbow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/rainbow/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX shared library librainbow.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rainbow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rainbow.dir/build: librainbow.so
.PHONY : CMakeFiles/rainbow.dir/build

CMakeFiles/rainbow.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rainbow.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rainbow.dir/clean

CMakeFiles/rainbow.dir/depend:
	cd /home/ubuntu/rainbow/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/rainbow /home/ubuntu/rainbow /home/ubuntu/rainbow/build /home/ubuntu/rainbow/build /home/ubuntu/rainbow/build/CMakeFiles/rainbow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rainbow.dir/depend
