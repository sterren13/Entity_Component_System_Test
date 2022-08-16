//
// Created by sterr on 11-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_STORAGE_H
#define ENTITY_COMPONENT_SYSTEM_TEST_STORAGE_H
#include <vector>
#include <unordered_map>

#include "Types.h"
#include "Archetype.h"
#include "ComponentManger.h"

// manger fore storing component data in archetypes

class Storage {
public:
    Storage(ComponentManger& componentManger);
    ~Storage();
    static Archetype_ID CalculateArchetypeID(ArchetypeBuilder& builder);
    Archetype_ID CreateArchetype(ArchetypeBuilder& builder);
    Archetype* GetArchetype(Archetype_ID archetypeId);
    void AddID(Entity_ID id);
    bool HasArchtype(Archetype_ID archetypeId);
private:
    ComponentManger& my_componentManger;
    std::unordered_map<Archetype_ID, Archetype*> ArchetypeID; // index from archetypeID to find ptr to archetype
    Archetype* RootArchetype;
    std::unordered_map<Type_ID, ArchetypeSet> Archetype_Set_Index; // Component to set of archetype set
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_STORAGE_H
