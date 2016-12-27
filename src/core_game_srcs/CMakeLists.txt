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
  ./srcs/PhysicComponent.cpp
  ./srcs/PhysicSystem.cpp
  ./srcs/PositionComponent.cpp
  ./srcs/SpriteComponent.cpp
  ./srcs/coreGameLib.cpp)
add_library(ecs ${SOURCES_CLIENT})
