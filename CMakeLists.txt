cmake_minimum_required(VERSION 3.22)
project(Entity_Component_System_Test)

set(CMAKE_CXX_STANDARD 20)

add_executable(Entity_Component_System_Test main.cpp Chunk.cpp Chunk.h TypeIdGenerator.h)
