# RTYPE ASKIP

cmake_minimum_required(VERSION 3.5)

project (RType)
set (RType_VERSION_MAJOR 1)
set (RType_VERSION_MINOR 0)
set(CMAKE_CXX_FLAGS "-Wall -std=c++14 -g3 -O0")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES_SERVER
  ./server/srcs/Main.cpp
  ./server/srcs/RTypeServer.cpp
  ./server/srcs/Client.cpp
  ./server/srcs/Message.cpp
  ./server/srcs/UnixSocket.cpp
  ./server/srcs/WinSocket.cpp
  ./server/srcs/NetworkHandler.cpp
  ./server/srcs/Room.cpp
  ./server/srcs/RoomManager.cpp
  ./server/srcs/CommandHandler.cpp
  ./server/srcs/CommandHandlerGame.cpp
)

set(INCLUDE_SERVER
  ./server/includes/ISocket.hpp
  ./server/includes/RTypeServer.hpp
  ./server/includes/Client.hpp
  ./server/includes/Message.hpp
  ./server/includes/UnixSocket.hpp
  ./server/includes/WinSocket.hpp
  ./server/includes/NetworkHandler.hpp
  ./server/includes/Room.hpp
  ./server/includes/RoomManager.hpp
  ./server/includes/CommandHandler.hpp
  ./server/includes/CommandHandlerGame.hpp
)

set(SOURCES_CLIENT_WIN32
  ./client/srcs/WinSocket.cpp)

set(SOURCES_CLIENT_UNIX
  ./client/srcs/UnixSocket.cpp)

set(SOURCES_ECS
./ECS/srcs/GameEngine.cpp
./ECS/srcs/EntityManager.cpp
./ECS/srcs/MessageBus.cpp
./ECS/srcs/ASystem.cpp
./ECS/srcs/SystemManager.cpp
)

set(SOURCES_CLIENT
  ./client/srcs/Main.cpp
  ./client/srcs/Core.cpp
  ./client/srcs/RTypeUI.cpp
  ./client/srcs/RTypeClient.cpp
  ./client/srcs/NetworkHandler.cpp
  ./client/srcs/Message.cpp
  ./client/srcs/CommandHandler.cpp
)

set(SOURCES_MSFML
  ./mSFML/AnimatedSprite.cpp
  ./mSFML/Animation.cpp
  ./mSFML/Audio.cpp
  ./mSFML/TextureManager.cpp
  ./mSFML/Timer.cpp
  ./mSFML/Window.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
include_directories(${INCLUDE_SERVER})
add_executable(RType_server WIN32 ${SOURCES_SERVER})
target_link_libraries(RType_server Threads::Threads)

include_directories("client/includes" "ECS/includes" ${CMAKE_CURRENT_SOURCE_DIR}/mSFML)
IF (WIN32)
  add_executable(RType_client WIN32 ${SOURCES_CLIENT} ${SOURCES_MSFML} ${SOURCES_CLIENT_WIN32} ${SOURCES_ECS})
ELSEIF (UNIX AND NOT MINGW)
  add_executable(RType_client ${SOURCES_CLIENT} ${SOURCES_MSFML} ${SOURCES_CLIENT_UNIX} ${SOURCES_ECS})
ENDIF()
target_link_libraries(RType_client Threads::Threads sfml-window sfml-system sfml-audio sfml-graphics dl)
