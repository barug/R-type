## CLIENT RTYPE ASKIP

cmake_minimum_required(VERSION 3.5)

function (client)
  project (client_rtype)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gameLibs)

  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/client/includes
    ${ECS_DIRECTORY}/includes
    ${SFML_DIRECTORY}
    ${CORE_GAME_LIB_DIRECTORY}/includes
  )

  set(
    SOURCES_CLIENT
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
    ${CMAKE_CURRENT_SOURCE_DIR}/client/srcs/GuiSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/client/srcs/SpriteComponent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/client/srcs/RTypeUI.cpp
  )

  add_library(
    client_rtype
    MODULE
    ${SOURCES_CLIENT}
  )

 target_link_libraries(client_rtype Threads::Threads sfml-window sfml-system sfml-audio sfml-graphics dl)

endfunction()