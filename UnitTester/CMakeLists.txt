PROJECT(UnitTester C)
cmake_minimum_required(VERSION 3.19)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES "*.c")
file(GLOB SOURCES "*.h")

add_executable(UnitTester
        TestMain.c
        TestMain.c
        Tester.h
        Tester.c
        Testscripts/FileManagerTest.h
        Testscripts/FileManagerTest.c
        Testscripts/ListTest.h
        Testscripts/ListTest.c
        Testscripts/PathTest.h
        Testscripts/PathTest.c
        ../ColorPrinter/ColorPrinter.h
        ../ColorPrinter/ColorPrinter.c
        ../List/List.h
        ../List/List.c
        ../SocketFileManager/Path.h
        ../SocketFileManager/Path.c
        ../SocketFileManager/OSError.h
        ../SocketFileManager/OSError.c
        ../SocketFileManager/PathList.h
        ../SocketFileManager/PathList.c
        ../SocketFileManager/FileManager.h
        ../SocketFileManager/FileManager.c
        )