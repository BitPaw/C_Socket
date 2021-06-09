cmake_minimum_required(VERSION 3.19)
project(BS1_Praktikum C)

set(CMAKE_C_STANDARD 11)

include_directories(SocketApplication)
include_directories(SocketSystem)
include_directories(SocketFileManager)

add_executable(BS1_Praktikum
        SocketApplication/main.h
        SocketApplication/main.c

        SocketApplication/CommandToken.h
        SocketApplication/CommandToken.c

        SocketSystem/Client.h
        SocketSystem/Client.c
        SocketSystem/Server.h
        SocketSystem/Server.c
        SocketSystem/Thread.h
        SocketSystem/Thread.c
        SocketSystem/SocketError.h
        SocketSystem/SocketError.c
        SocketSystem/AsyncLock.h
        SocketSystem/AsyncLock.c
        SocketSystem/OSDefine.h
        SocketSystem/IPVersion.h
        SocketSystem/IPVersion.c
        SocketSystem/IOSocket.h
        SocketSystem/IOSocket.c
        ColorPrinter/ColorPrinter.h
        ColorPrinter/ColorPrinter.c


)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)