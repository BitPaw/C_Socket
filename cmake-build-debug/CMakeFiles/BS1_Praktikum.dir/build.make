# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /home/jona/Schreibtisch/clion-2021.1.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/jona/Schreibtisch/clion-2021.1.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/BS1_Praktikum.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BS1_Praktikum.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BS1_Praktikum.dir/flags.make

CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.o: ../SocketApplication/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketApplication/main.c

CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketApplication/main.c > CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.i

CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketApplication/main.c -o CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.s

CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.o: ../SocketApplication/CommandToken.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketApplication/CommandToken.c

CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketApplication/CommandToken.c > CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.i

CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketApplication/CommandToken.c -o CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.s

CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.o: ../SocketSystem/Client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/Client.c

CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/Client.c > CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.i

CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/Client.c -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.s

CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.o: ../SocketSystem/Server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/Server.c

CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/Server.c > CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.i

CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/Server.c -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.s

CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.o: ../SocketSystem/Thread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/Thread.c

CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/Thread.c > CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.i

CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/Thread.c -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.s

CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.o: ../SocketSystem/SocketError.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/SocketError.c

CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/SocketError.c > CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.i

CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/SocketError.c -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.s

CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.o: ../SocketSystem/AsyncLock.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/AsyncLock.c

CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/AsyncLock.c > CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.i

CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/AsyncLock.c -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.s

CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.o: ../SocketSystem/IPVersion.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/IPVersion.c

CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/IPVersion.c > CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.i

CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/IPVersion.c -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.s

CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.o: ../SocketSystem/IOSocket.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/IOSocket.c

CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/IOSocket.c > CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.i

CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketSystem/IOSocket.c -o CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.s

CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.o: ../ColorPrinter/ColorPrinter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c

CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c > CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.i

CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c -o CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.s

CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.o: ../SocketApplication/UserSytem.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketApplication/UserSytem.c

CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketApplication/UserSytem.c > CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.i

CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketApplication/UserSytem.c -o CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.s

CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.o: ../SocketFileManager/FileManager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketFileManager/FileManager.c

CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketFileManager/FileManager.c > CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.i

CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketFileManager/FileManager.c -o CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.s

CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.o: ../SocketFileManager/PathList.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketFileManager/PathList.c

CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketFileManager/PathList.c > CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.i

CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketFileManager/PathList.c -o CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.s

CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.o: ../SocketFileManager/Path.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketFileManager/Path.c

CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketFileManager/Path.c > CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.i

CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/SocketFileManager/Path.c -o CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.s

CMakeFiles/BS1_Praktikum.dir/List/List.c.o: CMakeFiles/BS1_Praktikum.dir/flags.make
CMakeFiles/BS1_Praktikum.dir/List/List.c.o: ../List/List.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/BS1_Praktikum.dir/List/List.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/BS1_Praktikum.dir/List/List.c.o -c /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/List/List.c

CMakeFiles/BS1_Praktikum.dir/List/List.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/BS1_Praktikum.dir/List/List.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/List/List.c > CMakeFiles/BS1_Praktikum.dir/List/List.c.i

CMakeFiles/BS1_Praktikum.dir/List/List.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/BS1_Praktikum.dir/List/List.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/List/List.c -o CMakeFiles/BS1_Praktikum.dir/List/List.c.s

# Object files for target BS1_Praktikum
BS1_Praktikum_OBJECTS = \
"CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.o" \
"CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.o" \
"CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.o" \
"CMakeFiles/BS1_Praktikum.dir/List/List.c.o"

# External object files for target BS1_Praktikum
BS1_Praktikum_EXTERNAL_OBJECTS =

BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketApplication/main.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketApplication/CommandToken.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketSystem/Client.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketSystem/Server.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketSystem/Thread.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketSystem/SocketError.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketSystem/AsyncLock.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketSystem/IPVersion.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketSystem/IOSocket.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/ColorPrinter/ColorPrinter.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketApplication/UserSytem.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketFileManager/FileManager.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketFileManager/PathList.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/SocketFileManager/Path.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/List/List.c.o
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/build.make
BS1_Praktikum: CMakeFiles/BS1_Praktikum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C executable BS1_Praktikum"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BS1_Praktikum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BS1_Praktikum.dir/build: BS1_Praktikum

.PHONY : CMakeFiles/BS1_Praktikum.dir/build

CMakeFiles/BS1_Praktikum.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BS1_Praktikum.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BS1_Praktikum.dir/clean

CMakeFiles/BS1_Praktikum.dir/depend:
	cd /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug /home/jona/Schreibtisch/BSPraktikum/BS1_Praktikum_Socket/cmake-build-debug/CMakeFiles/BS1_Praktikum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BS1_Praktikum.dir/depend

