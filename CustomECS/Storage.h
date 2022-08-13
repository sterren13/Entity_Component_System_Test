//
// Created by sterr on 11-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_STORAGE_H
#define ENTITY_COMPONENT_SYSTEM_TEST_STORAGE_H
#include <vector>
#include <unordered_map>

#include "Types.h"
#include "Archetype.h"

// manger fore storing component data in archetypes

class Storage {
public:
    Storage();
    ~Storage();
    Archetype_ID CreateArchetype(ArchetypeBuilder& builder); // TODO sort component bay size and tag bay id size
    Archetype* GetArchetype(Archetype_ID archetypeId);
private:
    std::unordered_map<Archetype_ID, Archetype*> ArchetypeID; // index from archetypeID to find ptr to archetype
    std::unordered_map<Type_ID, ArchetypeSet> Archetype_Set_Index; // Component to set of archetype set
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_STORAGE_H
