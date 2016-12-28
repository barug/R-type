cmake_minimum_required(VERSION 3.5)
project (ClientRType)
set(CMAKE_CXX_FLAGS "-Wall -std=c++14")
set(CMAKE_BUILD_TYPE Release)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes
		${CMAKE_CURRENT_SOURCE_DIR}/../../ECS/includes
		${CMAKE_CURRENT_SOURCE_DIR}/../../mSFML
		${CMAKE_CURRENT_SOURCE_DIR}/../Client)
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
  ./../../mSFML/AnimatedSprite.cpp
  ./srcs/PhysicComponent.cpp
  ./srcs/PhysicSystem.cpp
  ./srcs/PositionComponent.cpp
  ./srcs/SpriteComponent.cpp
  ./srcs/coreGameLib.cpp)
add_library(client_rtype SHARED ${SOURCES_CLIENT})
