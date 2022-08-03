cmake_minimum_required(VERSION 3.22)
project(Entity_Component_System_Test)

set(CMAKE_CXX_STANDARD 20)

add_executable(Entity_Component_System_Test
        main.cpp
        #Entity_Component_System/ECS.cpp
        #Entity_Component_System/ECS.h
        #Entity_Component_System/EntityManger.cpp
        #Entity_Component_System/EntityManger.h
        Entity_Component_System/Component.h
        Entity_Component_System/Archetype.h
        Entity_Component_System/TypeIdGenerator.h
        Entity_Component_System/Block.cpp
        Entity_Component_System/Block.h
        #Entity_Component_System/ArchetypeContainer.cpp
        #Entity_Component_System/ArchetypeContainer.h
        )
