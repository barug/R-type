# RTYPE ASKIP

cmake_minimum_required(VERSION 3.5)
include(${CMAKE_CURRENT_SOURCE_DIR}/server/CMakeLists.txt)
server()
include(${CMAKE_CURRENT_SOURCE_DIR}/client/CMakeLists.txt)
client()
