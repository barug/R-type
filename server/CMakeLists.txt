# SERVER RTYPE ASKIP

cmake_minimum_required(VERSION 3.5)

project (server_rtype)

set (SERVER_VERSION_MAJOR 1)
set (SERVER_VERSION_MINOR 0)

set(CMAKE_CXX_FLAGS "-Wall -std=c++14 -g3 -O0")
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCES_SERVER
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

set(SOURCES_SERVER_WIN32
  ./srcs/WinSocket.cpp)

set(SOURCES_SERVER_UNIX
  ./srcs/UnixSocket.cpp)

set(INCLUDE_SERVER
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

set(INCLUDES_SERVER_WIN32
  ./includes/WinSocket.hpp)

set(INCLUDES_SERVER_UNIX
  ./includes/UnixSocket.hpp)

include_directories(./includes/)

IF (WIN32)
  add_executable(server_rtype WIN32 ${INCLUDE_SERVER} ${INCLUDES_SERVER_WIN32} ${SOURCES_SERVER} ${SOURCES_SERVER_WIN32})
ELSEIF (UNIX AND NOT MINGW)
  add_executable(server_rtype  ${INCLUDE_SERVER} ${INCLUDES_SERVER_UNIX} ${SOURCES_SERVER} ${SOURCES_SERVER_UNIX})
ENDIF()
target_link_libraries(server_rtype Threads::Threads)
