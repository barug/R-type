#!/bin/sh

g++ -std=c++14 -shared -o mods/lib-MyMonster.so -fPIC srcs/MyMonster.cpp srcs/EntityManager.cpp srcs/SystemManager.cpp -Iincludes/
