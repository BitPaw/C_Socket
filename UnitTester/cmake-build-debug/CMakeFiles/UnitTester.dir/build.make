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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/UnitTester.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/UnitTester.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/UnitTester.dir/flags.make

CMakeFiles/UnitTester.dir/TestMain.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/TestMain.c.o: ../TestMain.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/UnitTester.dir/TestMain.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/TestMain.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/TestMain.c

CMakeFiles/UnitTester.dir/TestMain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/TestMain.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/TestMain.c > CMakeFiles/UnitTester.dir/TestMain.c.i

CMakeFiles/UnitTester.dir/TestMain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/TestMain.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/TestMain.c -o CMakeFiles/UnitTester.dir/TestMain.c.s

CMakeFiles/UnitTester.dir/Tester.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/Tester.c.o: ../Tester.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/UnitTester.dir/Tester.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/Tester.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Tester.c

CMakeFiles/UnitTester.dir/Tester.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/Tester.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Tester.c > CMakeFiles/UnitTester.dir/Tester.c.i

CMakeFiles/UnitTester.dir/Tester.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/Tester.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Tester.c -o CMakeFiles/UnitTester.dir/Tester.c.s

CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.o: ../Testscripts/FileManagerTest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Testscripts/FileManagerTest.c

CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Testscripts/FileManagerTest.c > CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.i

CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Testscripts/FileManagerTest.c -o CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.s

CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.o: ../Testscripts/ListTest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Testscripts/ListTest.c

CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Testscripts/ListTest.c > CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.i

CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Testscripts/ListTest.c -o CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.s

CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.o: ../Testscripts/PathTest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Testscripts/PathTest.c

CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Testscripts/PathTest.c > CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.i

CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/Testscripts/PathTest.c -o CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.s

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.o: /Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c > CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.i

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.s

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.o: /Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c > CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.i

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.s

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.o: /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c > CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.i

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.s

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.o: /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c > CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.i

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.s

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.o: /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c > CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.i

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.s

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.o: CMakeFiles/UnitTester.dir/flags.make
CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.o: /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.o -c /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c > CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.i

CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c -o CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.s

# Object files for target UnitTester
UnitTester_OBJECTS = \
"CMakeFiles/UnitTester.dir/TestMain.c.o" \
"CMakeFiles/UnitTester.dir/Tester.c.o" \
"CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.o" \
"CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.o" \
"CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.o" \
"CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.o" \
"CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.o" \
"CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.o" \
"CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.o" \
"CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.o" \
"CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.o"

# External object files for target UnitTester
UnitTester_EXTERNAL_OBJECTS =

UnitTester: CMakeFiles/UnitTester.dir/TestMain.c.o
UnitTester: CMakeFiles/UnitTester.dir/Tester.c.o
UnitTester: CMakeFiles/UnitTester.dir/Testscripts/FileManagerTest.c.o
UnitTester: CMakeFiles/UnitTester.dir/Testscripts/ListTest.c.o
UnitTester: CMakeFiles/UnitTester.dir/Testscripts/PathTest.c.o
UnitTester: CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/ColorPrinter/ColorPrinter.c.o
UnitTester: CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/List/List.c.o
UnitTester: CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/Path.c.o
UnitTester: CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/OSError.c.o
UnitTester: CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/PathList.c.o
UnitTester: CMakeFiles/UnitTester.dir/Users/dennis/Desktop/BS1_Praktikum_Socket/SocketFileManager/FileManager.c.o
UnitTester: CMakeFiles/UnitTester.dir/build.make
UnitTester: CMakeFiles/UnitTester.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking C executable UnitTester"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/UnitTester.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/UnitTester.dir/build: UnitTester

.PHONY : CMakeFiles/UnitTester.dir/build

CMakeFiles/UnitTester.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/UnitTester.dir/cmake_clean.cmake
.PHONY : CMakeFiles/UnitTester.dir/clean

CMakeFiles/UnitTester.dir/depend:
	cd /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug /Users/dennis/Desktop/BS1_Praktikum_Socket/UnitTester/cmake-build-debug/CMakeFiles/UnitTester.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/UnitTester.dir/depend
