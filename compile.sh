#!/usr/bin/sh

cmake . && make -j4 && cd ECS/ && cmake . && make -j4 && cp ecs ../client/ && cd ..
