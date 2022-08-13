cmake_minimum_required(VERSION 3.22)
project(Entity_Component_System_Test)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/entt)

add_executable(Entity_Component_System_Test
        main.cpp
        CustomECS/Storage.cpp
        CustomECS/Storage.h
        CustomECS/Querie.cpp
        CustomECS/Querie.h
        CustomECS/Types.h CustomECS/Archetype.cpp CustomECS/Archetype.h CustomECS/ComponentManger.cpp CustomECS/ComponentManger.h CustomECS/Utilites.h CustomECS/ECS.cpp CustomECS/ECS.h CustomECS/Block.h)

target_link_libraries(Entity_Component_System_Test PUBLIC EnTT)