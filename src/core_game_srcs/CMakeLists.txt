cmake_minimum_required(VERSION 3.5)
project (ClientRType)
set(CMAKE_CXX_FLAGS "-Wall -std=c++14")
set(CMAKE_BUILD_TYPE Release)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes
		${CMAKE_CURRENT_SOURCE_DIR}/../../ECS/includes
		${CMAKE_CURRENT_SOURCE_DIR}/../../mSFML
		${CMAKE_CURRENT_SOURCE_DIR}/../Client)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCES_CLIENT
  ./srcs/GuiSystem.cpp
  ./../../ECS/srcs/EntityManager.cpp
  ./../../ECS/srcs/SystemManager.cpp
  ./../../ECS/srcs/MessageBus.cpp
  ./../../ECS/srcs/ASystem.cpp
  ./../../mSFML/Window.cpp
  ./../../mSFML/Timer.cpp
  ./../../mSFML/TextureManager.cpp
  ./../../mSFML/Animation.cpp
  ./../../mSFML/Audio.cpp
  ./../../mSFML/AnimatedSprite.cpp
  ./srcs/PhysicComponent.cpp
  ./srcs/PhysicSystem.cpp
  ./srcs/PositionComponent.cpp
  ./srcs/SpriteComponent.cpp
  ./srcs/coreGameLib.cpp)
add_library(client_rtype MODULE ${SOURCES_CLIENT})
target_link_libraries(client_rtype Threads::Threads sfml-window sfml-system sfml-audio sfml-graphics dl)
