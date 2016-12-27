#!/bin/sh

g++ -std=c++14 -shared -o mods/lib-MyMonster.so -fPIC srcs/MyMonster.cpp srcs/EntityManager.cpp srcs/SystemManager.cpp -Iincludes/
# g++ -std=c++14 -shared -o dynamicLibs/lib-AnotherMonster.so -fPIC srcs/AnotherMonster.cpp -Iincludes/
