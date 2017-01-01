# RTYPE ASKIP

cmake_minimum_required(VERSION 3.5)

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
# include(${CMAKE_CURRENT_SOURCE_DIR}/server/CMakeLists.txt)
# server()

# build Server
include(${CMAKE_CURRENT_SOURCE_DIR}/client/CMakeLists.txt)
client()

# build ecs
include(${CMAKE_CURRENT_SOURCE_DIR}/ECS/CMakeLists.txt)
ecs()
