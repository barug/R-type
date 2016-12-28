cmake_minimum_required(VERSION 3.5)
project (ClientRType)
set(CMAKE_CXX_FLAGS "-Wall -std=c++14")
set(CMAKE_BUILD_TYPE Release)

set(ECS_DIRECTORY ../ECS)
set(SFML_DIRECTORY ../mSFML)
set(CORE_GAME_LIB_DIRECTORY ../core_game_srcs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes
		${ECS_DIRECTORY}/includes
		${SFML_DIRECTORY}
		${CORE_GAME_LIB_DIRECTORY}/includes)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCES_CLIENT
  ${ECS_DIRECTORY}/srcs/EntityManager.cpp
  ${ECS_DIRECTORY}/srcs/SystemManager.cpp
  ${ECS_DIRECTORY}/srcs/MessageBus.cpp
  ${ECS_DIRECTORY}/srcs/ASystem.cpp
  ${SFML_DIRECTORY}/Window.cpp
  ${SFML_DIRECTORY}/Timer.cpp
  ${SFML_DIRECTORY}/TextureManager.cpp
  ${SFML_DIRECTORY}/Animation.cpp
  ${SFML_DIRECTORY}/Audio.cpp
  ${SFML_DIRECTORY}/AnimatedSprite.cpp
  ${CORE_GAME_LIB_DIRECTORY}/srcs/PhysicSystem.cpp
  ${CORE_GAME_LIB_DIRECTORY}/srcs/PhysicComponent.cpp
  ${CORE_GAME_LIB_DIRECTORY}/srcs/PositionComponent.cpp
  ${CORE_GAME_LIB_DIRECTORY}/srcs/coreGameLib.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/srcs/GuiSystem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/srcs/SpriteComponent.cpp
  )
  
add_library(client_rtype MODULE ${SOURCES_CLIENT})
target_link_libraries(client_rtype sfml-window sfml-system sfml-audio sfml-graphics)
