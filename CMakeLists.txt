cmake_minimum_required(VERSION 3.19)
project(BS1_Praktikum C)

set(CMAKE_C_STANDARD 11)

include_directories(SocketApplication)
include_directories(SocketSystem)
include_directories(SocketFileManager)
include_directories(ColorPrinter)
include_directories(List)

add_executable(BS1_Praktikum
        SocketApplication/main.h
        SocketApplication/main.c

        SocketApplication/ApplicationState.c
        SocketApplication/ApplicationState.h
        SocketApplication/Command.h
        SocketApplication/CommandError.h
        SocketApplication/CommandToken.h
        SocketApplication/CommandToken.c
        SocketApplication/CommunicationRole.h
        SocketApplication/FileError.h
        SocketApplication/resource.h

        SocketApplication/UserSytem.h
        SocketApplication/UserSytem.c

        SocketApplication/Command.h

        SocketApplication/SocketApplicationData.c
        SocketApplication/SocketApplicationData.h

        SocketFileManager/OSError.c
        SocketFileManager/OSError.h
        SocketFileManager/FileManager.h
        SocketFileManager/FileManager.c
        SocketFileManager/PathList.h
        SocketFileManager/PathList.c
        SocketFileManager/Path.h
        SocketFileManager/Path.c



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

        SocketApplication/UserSytem.h
        SocketApplication/UserSytem.c


        List/List.h
        List/List.c


)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)