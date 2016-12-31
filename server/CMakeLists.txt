## SERVER RTYPE ASKIP

cmake_minimum_required(VERSION 3.5)

function (server)
  project (server_rtype_ecs)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/serverLibs)
  
  include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/server/includes_ecs
    ${ECS_DIRECTORY}/includes
    ${SFML_DIRECTORY}
    ${CORE_GAME_LIB_DIRECTORY}/includes
  )

set(SOURCES_ECS_SERVER
    ${ECS_DIRECTORY}/srcs/EntityManager.cpp
    ${ECS_DIRECTORY}/srcs/SystemManager.cpp
    ${ECS_DIRECTORY}/srcs/MessageBus.cpp
    ${ECS_DIRECTORY}/srcs/ASystem.cpp
    ${CORE_GAME_LIB_DIRECTORY}/srcs/PhysicSystem.cpp
    ${CORE_GAME_LIB_DIRECTORY}/srcs/PhysicComponent.cpp
    ${CORE_GAME_LIB_DIRECTORY}/srcs/PositionComponent.cpp
    ${CORE_GAME_LIB_DIRECTORY}/srcs/HitBoxComponent.cpp
    ${CORE_GAME_LIB_DIRECTORY}/srcs/CollisionSystem.cpp
    ${CORE_GAME_LIB_DIRECTORY}/srcs/HealthComponent.cpp
    ${CORE_GAME_LIB_DIRECTORY}/srcs/ScriptComponent.cpp
    ${CORE_GAME_LIB_DIRECTORY}/srcs/ScriptSystem.cpp
    ${CORE_GAME_LIB_DIRECTORY}/srcs/BasicMonsterScript.cpp
    ${CORE_GAME_LIB_DIRECTORY}/srcs/HealthSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/coreGameLib.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/GuiSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/SpriteComponent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/PlayerInputSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/PlayerInputComponent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/RTypeUI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/NetworkSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/RTypeClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/CommandHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/NetworkHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/UnixSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/WinSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server/srcs_ecs/Message.cpp 
  )

  add_library(
    server_rtype_ecs
    MODULE
    ${SOURCES_ECS_SERVER}
  )

 target_link_libraries(server_rtype_ecs Threads::Threads sfml-window sfml-system sfml-audio sfml-graphics)
 
  project (server_rtype)
  set(CMAKE_CXX_FLAGS "-Wall -std=c++14 -Wl,-z,defs")

  set(CMAKE_INCLUDE_CURRENT_DIR ON)


## Includes & Sources

  set(INCLUDES_SERVER_RTYPE
    ./server/includes/ISocket.hpp
    ./server/includes/RTypeServer.hpp
    ./server/includes/Client.hpp
    ./server/includes/Message.hpp
    ./server/includes/NetworkHandler.hpp
    ./server/includes/Room.hpp
    ./server/includes/RoomManager.hpp
    ./server/includes/CommandHandler.hpp
    ./server/includes/CommandHandlerGame.hpp
    ./ECS/srcs/GameEngine.cpp
    ./ECS/srcs/EntityManager.cpp
    ./ECS/srcs/SystemManager.cpp
    ./ECS/srcs/MessageBus.cpp
    ./ECS/srcs/ASystem.cpp
  )

  set(INCLUDES_SERVER_RTYPE_WIN32
    ./server/includes/WinSocket.hpp
  )

  set(INCLUDES_SERVER_RTYPE_UNIX
    ./server/includes/UnixSocket.hpp
  )

  set(SOURCES_SERVER_RTYPE
    ./server/srcs/Main.cpp
    ./server/srcs/RTypeServer.cpp
    ./server/srcs/Client.cpp
    ./server/srcs/Message.cpp
    ./server/srcs/NetworkHandler.cpp
    ./server/srcs/Room.cpp
    ./server/srcs/RoomManager.cpp
    ./server/srcs/CommandHandler.cpp
    ./server/srcs/CommandHandlerGame.cpp
  )

  set(SOURCES_SERVER_RTYPE_WIN32
    ./server/srcs/WinSocket.cpp
  )

  set(SOURCES_SERVER_RTYPE_UNIX
    ./server/srcs/UnixSocket.cpp
  )

  include_directories(
    ./server/includes/
  )

  IF (WIN32)
    add_executable(server_rtype
      WIN32
      ${SOURCES_SERVER_RTYPE}
      ${SOURCES_SERVER_RTYPE_WIN32}
      ${INCLUDES_SERVER_RTYPE}
      ${INCLUDES_SERVER_RTYPE_WIN32}
    )
  ELSEIF (UNIX AND NOT MINGW)
    add_executable(server_rtype
      ${SOURCES_SERVER_RTYPE}
      ${SOURCES_SERVER_RTYPE_UNIX}
      ${INCLUDES_SERVER_RTYPE}
      ${INCLUDES_SERVER_RTYPE_UNIX}
    )
  ENDIF()

  target_link_libraries(server_rtype Threads::Threads dl)

endfunction()
