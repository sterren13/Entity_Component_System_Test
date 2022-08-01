//
// Created by sterr on 1-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPECONTAINER_H
#define ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPECONTAINER_H
#include <vector>
#include "Block.h"
#include "TypeIdGenerator.h"

class ArchetypeContainer {
public:
    ArchetypeContainer();
    ~ArchetypeContainer();
private:
    std::vector<Block> Blocks;
    std::vector<EntityID> Entitys;
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPECONTAINER_H
