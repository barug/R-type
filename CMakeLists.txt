# RTYPE ASKIP

cmake_minimum_required(VERSION 3.5)

<<<<<<< HEAD
project (RType)
set (RType_VERSION_MAJOR 1)
set (RType_VERSION_MINOR 0)
set(CMAKE_CXX_FLAGS "-Wall -std=c++14 -g3 -O0")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories({CURRENT})
include_directories(ECS/includes)

set(SOURCES_SERVER
  ./src/Server/Main.cpp
  ./src/Server/RTypeServer.cpp
  ./src/Server/Client.cpp
  ./src/Server/Message.cpp
  ./src/Server/UnixSocket.cpp
  ./src/Server/WinSocket.cpp
  ./src/Server/NetworkHandler.cpp
  ./src/Server/Room.cpp
  ./src/Server/RoomManager.cpp
  ./src/Server/CommandHandler.cpp
  ./src/Server/CommandHandlerGame.cpp
)

set(SOURCES_CLIENT_WIN32
  ./src/Client/WinSocket.cpp)

set(SOURCES_CLIENT_UNIX
  ./src/Client/UnixSocket.cpp)

set(SOURCES_ECS
./ECS/srcs/GameEngine.cpp
./ECS/srcs/EntityManager.cpp
./ECS/srcs/MessageBus.cpp
./ECS/srcs/GraphicSystem.cpp
./ECS/srcs/PhysicComponent.cpp
./ECS/srcs/ASystem.cpp
./ECS/srcs/PhysicSystem.cpp
./ECS/srcs/SystemManager.cpp
./ECS/srcs/InputSystem.cpp
)

set(SOURCES_CLIENT
  ./src/Client/Main.cpp
  ./src/Client/Core.cpp
  ./src/Client/RTypeUI.cpp
  ./src/Client/RTypeClient.cpp
  ./src/Client/NetworkHandler.cpp
  ./src/Client/Message.cpp
  ./src/Client/CommandHandler.cpp
)

set(SOURCES_MSFML
  ./mSFML/AnimatedSprite.cpp
  ./mSFML/Animation.cpp
  ./mSFML/Audio.cpp
  ./mSFML/TextureManager.cpp
  ./mSFML/Timer.cpp
  ./mSFML/Window.cpp
)

add_executable(RType_server WIN32 ${SOURCES_SERVER})
target_link_libraries(RType_server Threads::Threads)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mSFML)
IF (WIN32)
  add_executable(RType_client WIN32 ${SOURCES_CLIENT} ${SOURCES_MSFML} ${SOURCES_CLIENT_WIN32} ${SOURCES_ECS})
ELSEIF (UNIX AND NOT MINGW)
  add_executable(RType_client ${SOURCES_CLIENT} ${SOURCES_MSFML} ${SOURCES_CLIENT_UNIX} ${SOURCES_ECS})
ENDIF()
target_link_libraries(RType_client Threads::Threads sfml-window sfml-system sfml-audio sfml-graphics dl)
=======
# Relaease Type & Nb
set (CMAKE_BUILD_TYPE Release)
set (SERVER_RTYPE_VERSION_MAJOR 1)
set (SERVER_RTYPE_VERSION_MINOR 0)
set (CLIENT_RTYPE_VERSION_MAJOR 1)
set (CLIENT_RTYPE_VERSION_MINOR 0)

# C++ Flags
set (CMAKE_CXX_FLAGS "-Wall -std=c++14 -g3 -O0")

# C++ 14
set (CMAKE_CXX_STANDARD 14)

# C++ Thread
set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)

# Directory
set (ECS_DIRECTORY ./ECS)
set (SFML_DIRECTORY ./mSFML)
set (CORE_GAME_LIB_DIRECTORY ./core_game_srcs)

# build Client
include(${CMAKE_CURRENT_SOURCE_DIR}/server/CMakeLists.txt)
server()

# build Server
include(${CMAKE_CURRENT_SOURCE_DIR}/client/CMakeLists.txt)
client()
>>>>>>> cf728acab5a651662cf3d44c2c66f58075a29e99
