cmake_minimum_required(VERSION 3.19)
project(BS1_Praktikum C)

set(CMAKE_C_STANDARD 11)

include_directories(SocketApplication)

add_executable(BS1_Praktikum
        SocketApplication/main.c
        SocketFileManager/DeleteMe.c
        SocketSystem/Client.c
        SocketSystem/Client.h
        SocketSystem/Command.h
        SocketSystem/CommandToken.c
        SocketSystem/CommandToken.h
        SocketSystem/ConnectionState.c
        SocketSystem/ConnectionState.h
        SocketSystem/IOSocket.c
        SocketSystem/IOSocket.h
        SocketSystem/Server.c
        SocketSystem/Server.h
        SocketSystem/SocketErrorCode.h
        SocketSystem/Thread.c
        SocketSystem/Thread.h)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)