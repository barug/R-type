## SERVER RTYPE ASKIP

cmake_minimum_required(VERSION 3.5)

function (server)
  project (server_rtype)

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

  target_link_libraries(server_rtype Threads::Threads)

endfunction()
