## SERVER RTYPE ASKIP

cmake_minimum_required(VERSION 3.5)
project (server_rtype)

set (SERVER_RTYPE_VERSION_MAJOR 1)
set (SERVER_RTYPE_VERSION_MINOR 0)

set(CMAKE_CXX_FLAGS "-Wall -std=c++14 -g3 -O0")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${server_rtype_SOURCE_DIR}/..)

## Thread Flag

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

## Includes & Sources

set(INCLUDES_SERVER_RTYPE
  ./includes/ISocket.hpp
  ./includes/RTypeServer.hpp
  ./includes/Client.hpp
  ./includes/Message.hpp
  ./includes/NetworkHandler.hpp
  ./includes/Room.hpp
  ./includes/RoomManager.hpp
  ./includes/CommandHandler.hpp
  ./includes/CommandHandlerGame.hpp
)

set(INCLUDES_SERVER_RTYPE_WIN32
  ./includes/WinSocket.hpp
)

set(INCLUDES_SERVER_RTYPE_UNIX
  ./includes/UnixSocket.hpp
)

set(SOURCES_SERVER_RTYPE
  ./srcs/Main.cpp
  ./srcs/RTypeServer.cpp
  ./srcs/Client.cpp
  ./srcs/Message.cpp
  ./srcs/NetworkHandler.cpp
  ./srcs/Room.cpp
  ./srcs/RoomManager.cpp
  ./srcs/CommandHandler.cpp
  ./srcs/CommandHandlerGame.cpp
)

set(SOURCES_SERVER_RTYPE_WIN32
  ./srcs/WinSocket.cpp
)

set(SOURCES_SERVER_RTYPE_UNIX
  ./srcs/UnixSocket.cpp
)

include_directories(./includes/)

IF (WIN32)
  add_executable(server_rtype WIN32 ${SOURCES_SERVER_RTYPE} ${SOURCES_SERVER_RTYPE_WIN32} ${INCLUDES_SERVER_RTYPE} ${INCLUDES_SERVER_RTYPE_WIN32})
ELSEIF (UNIX AND NOT MINGW)
  add_executable(server_rtype ${SOURCES_SERVER_RTYPE} ${SOURCES_SERVER_RTYPE_UNIX} ${INCLUDES_SERVER_RTYPE} ${INCLUDES_SERVER_RTYPE_UNIX})
ENDIF()
target_link_libraries(server_rtype Threads::Threads)
