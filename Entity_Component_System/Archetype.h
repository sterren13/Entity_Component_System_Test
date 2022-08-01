//
// Created by sterr on 31-7-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPE_H
#define ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPE_H
#include "TypeIdGenerator.h"
#include "Component.h"
#include <vector>

struct Archetype {
    ArchetypeID ID;
    std::vector<ComponentTypeID> Components;
    std::vector<TypeComponent> Component_properties;
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPE_H
